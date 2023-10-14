#pragma once 

#include "ecsUtils.hpp"
#include "component.hpp"
#include "component_container.hpp"

#include <any>
#include <unordered_map>
#include <vector>
#include<iostream>
#include<execution>

namespace engine {
	class EntityComponentManager {
	public:
		EntityComponentManager() {};
		~EntityComponentManager() {};


		template<typename T>
		void registerComponent() {
			componentContainerPool.emplace(getTypeName<T>(), std::make_shared<ComponentContainer<T>>());
		}


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
		void bindComponent(Entity entity, Component<T> component) {
			assertEntityExists(entity);

			// Generate an id for the component 
			if (!freeComponentIds.empty()) {
				component.setId(freeComponentIds.back());
				freeComponentIds.pop_back();
			}
			else {
				component.setId(nextAvalibleId++);
			}
			auto id = component.getId();
			auto componentType = getTypeName<T>();

			// Bind component
			getComponentContainer<T>()->add(id, component);
			entityOwnershipMap[entity].emplace(id, componentType);
			componentToEntityMap.emplace(id, entity);
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

	private:
		  //------------------------//
		 //      Entity Data       //
		//------------------------//
		std::vector<Entity> entities{};
		std::vector<Entity> freeEntities{};
		std::unordered_map<Entity, std::unordered_map<ComponentId, ContainerTypeName>> entityOwnershipMap{};

		  //------------------------//
		 //     Component Data     //
		//------------------------//
		ComponentId nextAvalibleId = 0;
		std::vector<ComponentId> freeComponentIds{};
		std::unordered_map<ComponentId, Entity> componentToEntityMap{};
		std::unordered_map<ContainerTypeName, std::shared_ptr<BaseComponentContainer>> componentContainerPool{};



		void assertEntityExists(Entity entity) {
			assert(std::find(entities.begin(), entities.end(), entity) != entities.end() && "EntityComponentManagerError: entity does not exist ");
		}

		template<typename T>
		std::shared_ptr<ComponentContainer<T>> getComponentContainer() {
			const char* containerType = getTypeName<T>();

			if (auto search = componentContainerPool.find(containerType); search != componentContainerPool.end()) {
				return std::static_pointer_cast<ComponentContainer<T>>(componentContainerPool[containerType]);
			}
			else {
				throw std::runtime_error("SceneError: tried to find a container for an unregisterd component type...' ");
			}
		}

		std::shared_ptr<ComponentContainer<std::any>> getComponentContainer(ContainerTypeName containerType) {
			return std::static_pointer_cast<ComponentContainer<std::any>>(componentContainerPool[containerType]);
		}
	};
}