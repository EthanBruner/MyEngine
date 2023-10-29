#pragma once

#include "utils.hpp"
#include "component.hpp"

#include <memory>

namespace engine {

	class System {
	public:
		virtual void update() = 0;
	};
}