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

		EntityComponentSystem();
		~EntityComponentSystem() {};


		// --- Entity Functions --- //
		template<typename... T>
		Entity& createEntity(T&&... comps) {
			Entity newEntity{};
			// Create a id to represent the entity
			if (!freeEntities.empty()) {
				newEntity = freeEntities.back();
				entities.emplace(newEntity);
				freeEntities.pop_back();
			}
			else {
				newEntity = entities.size() + 1;
				entities.emplace_back(newEntity);
			}

			entityOwnershipMap.emplace(newEntity, std::unordered_map<ComponentId, ContainerTypeName>());

			([&] { bindComponent(newEntity, comps); } (), ...);

			return entities.back();
		}


		void removeEntity(Entity entity);


		// --- Component Functions --- //
		template<typename... T>
		void registerComponents() {
			([] { 
				componentContainerPool->emplace(getTypeName<T>(), std::make_shared<ComponentContainer<T>>());
			}(), ...);
		}


		// ---  System Functions ---- //
		template <typename T, typename... SysArgs>
		void insertSystem(SysArgs... args) {
			auto name = getTypeName<T>();

			if (systems.find(name) != systems.end()) {
				throw std::runtime_error("EntityComponentSystemError: cannot insert multiple of a system type...");
			} 
			else {
				std::shared_ptr<System> system = std::static_pointer_cast<System>(std::make_shared<T>(std::forward<SysArgs>(args)...));
				system->bindMediator(systemMediator);
				systems.emplace(name, system);
			}
		}
		

		template <typename T, typename... SysArgs>
		void setMainSystem(SysArgs... args) {
			insertSystem<T>(std::forward<SysArgs>(args)...);
			mainSys = getTypeName<T>();
		}
		
		void feedMainSystemLoop(std::function<void()> func);
		void update();
		

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
		friend class SystemMediator;
		std::shared_ptr<SystemMediator> systemMediator;

		SystemTypeName mainSys;
		std::unordered_map<SystemTypeName, std::shared_ptr<System>> systems{};

		
		
		// --- Private Functions --- // 

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


		void assertEntityExists(Entity entity);
		Entity& findComponentOwner(ComponentId id);
	};
}
