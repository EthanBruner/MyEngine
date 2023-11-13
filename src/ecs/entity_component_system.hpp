#pragma once 

#include "utils.hpp"
#include "components.hpp"
#include "component_container.hpp"
#include "system.hpp"

#include <any>
#include <unordered_map>
#include <vector>


namespace engine {
	using EntityOnwershipMap = std::unordered_map<Entity, std::unordered_map<ComponentId, ContainerTypeName>>;

	class EntityComponentSystem {
	public:
		EntityComponentSystem() : componentContainerPool{ std::make_shared<ContainerPool>() } {};
		~EntityComponentSystem() {};

		// --- Entity Functions --- //
		template<typename... T>
		Entity& createEntity(T&&... comps) {
			Entity newEntity{};
			// Create a id to represent the entity
			if (!freeEntities.empty()) {
				newEntity = freeEntities.back();
				freeEntities.pop_back();
			}
			else {
				newEntity = entities.size() + 1;
				entities.emplace_back(newEntity);
			}

			entityOwnershipMap.emplace(newEntity, std::unordered_map<ComponentId, ContainerTypeName>());

			// iter & bind components
			([&] { bindComponent(newEntity, comps); } (), ...);

			return entities.back();
		}


		void removeEntity(Entity entity) {
			assertEntityExists(entity);

			entities.erase(std::find(entities.begin(), entities.end(), entity));
			freeEntities.emplace_back(entity);

			for (auto& [id, containerType] : entityOwnershipMap[entity]) {
				getComponentContainer(containerType)->remove(id);
				componentToEntityMap.erase(id);
			}
			entityOwnershipMap.erase(entity);
		}


		// --- Component Functions --- //
		template<typename... T>
		void registerComponents() {
			([&] { 
				componentContainerPool->emplace(getTypeName<T>(), std::make_shared<ComponentContainer<T>>());
			}(), ...);
		}

		template<typename T>
		ComponentMap<T>& retrieveComponents() {
			auto container = getComponentContainer<T>();
			return container->getComponents();
		}



		// ---  System Functions ---- //

		// NOTE: Expects arguments required to construct system excluding ecs pointer (should be first parameter of subsystem constructor)
		template <typename T, typename... SysArgs>
		void insertSystem(SysArgs... args) {
			auto parentEcs = std::make_shared<EntityComponentSystem>(*this);
			std::shared_ptr<System> system = std::static_pointer_cast<System>(std::make_shared<T>(parentEcs, std::forward<SysArgs>(args)...));

			systems.emplace(getTypeName<T>(), system);
		}


		template<typename T>
		std::shared_ptr<T> getSystem() {
			auto sysName = getTypeName<T>();
			if (systems.find(sysName) == systems.end()) {
				throw std::runtime_error("EntityComponentSystemError: cannot get a system that does not exist...");
			}
			else {
				return std::static_pointer_cast<T>(systems.at(sysName));
			}
		}


		void update() {
			for (auto&[key, sys] : systems) {
				sys->update();
			}
		}

	private:
		// --- Entity Members --- //
		std::vector<Entity> entities{};
		std::vector<Entity> freeEntities{};
		EntityOnwershipMap entityOwnershipMap{};

		// --- Component Members --- //
		std::shared_ptr<ContainerPool> componentContainerPool{};
		std::unordered_map<ComponentId, Entity> componentToEntityMap{};
		std::vector<ComponentId> freeComponentIds{};

		// --- System Members --- //
		std::unordered_map<SystemTypeName, std::shared_ptr<System>> systems{};



		// --- Private Functions --- // 
		void assertEntityExists(Entity entity) {
			assert(std::find(entities.begin(), entities.end(), entity) != entities.end() && "EntityComponentSystemError: entity does not exist ");
		}


		template<typename T>
		void bindComponent(Entity entity, T component) {
			assertEntityExists(entity);
			auto componentType = getTypeName<T>();

			// Generate Component id
			static std::size_t nextAvalibleId = 0;
			std::size_t id;
			if (!freeComponentIds.empty()) {
				id = freeComponentIds.back();
				freeComponentIds.pop_back();
			}
			else {
				id = nextAvalibleId++;
			}

			// Bind component
			getComponentContainer<T>()->add(id, component);
			entityOwnershipMap[entity].emplace(id, componentType);
			componentToEntityMap.emplace(id, entity);
		}

		template<typename T>
		bool hasComonentType(Entity& entity, T componentType) {
			assertEntityExists(entity);

			if (auto entityBindings = entityOwnershipMap[entity]; entityBindings.find(getTypeName<T>()) == entityBindings.end()) {
				return false;
			}
			else {
				return true;
			}
		}


		Entity& findComponentOwner(ComponentId id) {
			assert(componentToEntityMap.find(id) != componentToEntityMap.end() && "EntityComponentManagerError: Cannot find the owner of an unbinded component...");
			return componentToEntityMap[id];
		}


		template<typename T>
		std::shared_ptr<ComponentContainer<T>> getComponentContainer() {
			const char* containerType = getTypeName<T>();

			if (auto search = componentContainerPool->find(containerType); search != componentContainerPool->end()) {
				return std::static_pointer_cast<ComponentContainer<T>>(componentContainerPool->at(containerType));
			}
			else {
				throw std::runtime_error("SceneError: tried to find a container for an unregisterd component type...' ");
			}
		}
		std::shared_ptr<ComponentContainer<std::any>> getComponentContainer(ContainerTypeName containerType) {
			return std::static_pointer_cast<ComponentContainer<std::any>>(componentContainerPool->at(containerType));
		}
	};
}
