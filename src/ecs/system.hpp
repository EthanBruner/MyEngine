#pragma once

#include "utils.hpp"
#include "component_container.hpp"

#include <memory>

namespace engine {

	class System {
	public:
		virtual void init(std::shared_ptr<ContainerPool> container_pool, std::vector<std::shared_ptr<System>> system_pool) { 
			containerPool = container_pool; 
		};
		virtual void update() {};
		virtual std::size_t size() = 0;

		template<typename T>
		ComponentMap<T>& retrieve(std::shared_ptr<ContainerPool> container_pool) {
			auto componentTypeOfInterest = getTypeName<T>();

			if ( container_pool->find( componentTypeOfInterest ) != container_pool->end() ) {
				auto base = container_pool->at(componentTypeOfInterest);
				auto container = std::static_pointer_cast<ComponentContainer<T>>(base);
				ComponentMap<T>& components = container->getComponents();
				return components;
 			}
			else {
				throw std::runtime_error("SystemError: tried to retrieve a container pool that does not exist");
			}
		}

	protected:
		std::shared_ptr<ContainerPool> containerPool;

	};
}