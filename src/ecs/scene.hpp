#pragma once

#include "ecsUtils.hpp"
#include "entity_component_manager.hpp"
#include "system_manager.hpp"

#include <iostream>
#include <typeinfo>
#include <memory>
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <string>


namespace engine {

	// General Manarger and Interface for the Entity Compnent System
	class Scene {
	public:
		Scene() : entityComponentManager{ std::make_unique<EntityComponentManager>() }, systemManager{ std::make_unique<SystemManager>() } {};
		~Scene() {};

		//--------------------------------------------//
		// EntityComponentManager Shorthand Functions //
		//--------------------------------------------//
		template<typename T>
		void registerComponent() {
			entityComponentManager->registerComponent<T>();
		}


		template<typename... T>
		Entity& createEntity(Component<T>&&... comps) {
			return entityComponentManager->createEntity(std::forward<Component<T>>(comps)...);
			
		}

	private:
		std::unique_ptr <EntityComponentManager> entityComponentManager;
		std::unique_ptr<SystemManager> systemManager;

	};
}
