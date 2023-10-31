#pragma once

#include "utils.hpp"
#include "component_container.hpp"

#include <memory>

namespace engine {

	class System {
	public:
		virtual void update(std::shared_ptr<ContainerPool> containerpool) = 0;
		virtual std::size_t size() = 0;
	};
}