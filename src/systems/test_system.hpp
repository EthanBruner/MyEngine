#pragma once

#include "../ecs/system.hpp"

namespace engine {
	class TestSystem : public System {
		virtual void update() {};
	};
}