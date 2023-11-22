#pragma once

#include "entity_component_system.hpp"

namespace engine {

	class SystemMediator {
	public:
		
		SystemMediator(std::shared_ptr<EntityComponentSystem> parentEcs) : ecs{ parentEcs } {};

		template<typename T>
		std::shared_ptr<T> retrieveSystem() {
			auto sysName = getTypeName<T>();
			if (ecs->systems.find(sysName) == ecs->systems.end()) {
				throw std::runtime_error("EntityComponentSystemError: cannot get a system that does not exist...");
			}
			else {
				return std::static_pointer_cast<T>(ecs->systems.at(sysName));
			}
		}

		template<typename T>
		ComponentMap<T>& retrieveComponents() {
			auto container = ecs->getComponentContainer<T>();
			return container->getComponents();
		}

	private:
		std::shared_ptr<EntityComponentSystem> ecs;
	};
}