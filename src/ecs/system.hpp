#pragma once

#include <typeinfo>
#include <iostream>
#include <memory>

namespace engine {

	class System {
	public:
		virtual void update() = 0;
	};
}