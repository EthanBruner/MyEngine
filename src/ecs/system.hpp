#pragma once

#include "utils.hpp"
#include "component_container.hpp"

#include <memory>

namespace engine {

	class System {
	public:
		// NOTE: if container pool was class selecting component containers would be easier
		virtual void update(std::shared_ptr<ContainerPool> containerpool) = 0;
	};
}