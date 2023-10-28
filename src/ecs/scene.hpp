#pragma once

#include "ecsUtils.hpp"
#include "entity_component_manager.hpp"
#include "system_manager.hpp"

#include <iostream>


namespace engine {

	/* Interface for the Entity Compnent System
	and liaison for entities and systems. */
	class Scene: protected EntityComponentManager, protected SystemManager {
	public:
		Scene() {};
		~Scene() {};

		using EntityComponentManager::createEntity;
		using EntityComponentManager::registerComponent;
		using EntityComponentManager::registerComponentList;

		using SystemManager::insertSystem;
		using SystemManager::update;




		
	private:

	};
}
