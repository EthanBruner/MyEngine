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

	// Interface for the Entity Compnent System
	class Scene: public EntityComponentManager, public SystemManager {
	public:
		Scene() {};
		~Scene() {};

		using EntityComponentManager::createEntity;
		using EntityComponentManager::registerComponent;

		
	private:

	};
}
