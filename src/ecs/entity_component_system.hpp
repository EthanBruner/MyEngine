#pragma once 

#include "utils.hpp"
#include "component.hpp"
#include "component_container.hpp"

#include <any>
#include <unordered_map>
#include <vector>
#include <set>
#include<iostream>
#include<execution>


namespace engine {
	using EntityOnwershipMap = std::unordered_map<Entity, std::unordered_map<ComponentId, ContainerTypeName>>;

	class EntityComponentSystem {
	public:
		EntityComponentSystem() : componentContainerPool{ std::make_shared<ContainerPool>() } {};
		~EntityComponentSystem() {};


		template<typename... T>
		Entity& createEntity(Component<T>&&... comps) {
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


		template<typename T>
		void registerComponent() {
			componentContainerPool->emplace(getTypeName<T>(), std::make_shared<ComponentContainer<T>>());
		}

		template<typename... T>
		void registerComponentList() {
			([&] { registerComponent<T>(); }(), ...);
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


		template <typename T, typename... SysArgs>
		void insertSystem(SysArgs... args) {
			auto system = std::static_pointer_cast<System>(std::make_shared<T>(std::forward<SysArgs>(args)...));
			systems.emplace_back(system);
		}


		// NOTE: Just pray to god no two systems ever have the same size
		template<typename T>
		std::shared_ptr<T> getSystem() {
			for (auto& sys : systems) {
				if (sizeof(T) == sys->size()) {
					return convertSystem<T>(sys);
				}
			};
			throw std::runtime_error("EntityComponentSystemError: cannot get a system that does not exist");
		}


		void update() {
			for (auto& sys : systems) {
				sys->update(componentContainerPool);
			}
		}




	private:
		// --- Entity Data --- //
		std::vector<Entity> entities{};
		std::vector<Entity> freeEntities{};
		EntityOnwershipMap entityOwnershipMap{};

		// --- Component Data --- //
		std::shared_ptr<ContainerPool> componentContainerPool{};
		std::unordered_map<ComponentId, Entity> componentToEntityMap{};
		std::vector<ComponentId> freeComponentIds{};

		// --- System Data --- //
		std::vector<std::shared_ptr<System>> systems{};



		void assertEntityExists(Entity entity) {
			assert(std::find(entities.begin(), entities.end(), entity) != entities.end() && "EntityComponentSystemError: entity does not exist ");
		}


		template<typename T>
		void bindComponent(Entity entity, Component<T> component) {
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
		bool hasComonentType(Entity& entity, Component<T> componentType) {
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


		template<typename To, typename From>
		std::shared_ptr<To> convertSystem(From sys) {
			return std::static_pointer_cast<To>(sys);
		}

	};
}