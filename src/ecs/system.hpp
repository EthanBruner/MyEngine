#pragma once

#include "ecsUtils.hpp"
#include "component.hpp"

#include <memory>

namespace engine {

	class System {
	public:
		virtual void update(std::shared_ptr<ContainerPool> containerPool) = 0;
	};
}