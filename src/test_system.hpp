#pragma once

#include "ecs/system.hpp"

namespace engine {

	class TestSystem : public System {
	public:
		TestSystem(int a, double b): a{ a }, b{ b } {};

		virtual void update(std::shared_ptr<ContainerPool> containerpool) {};

	private:
		int a ;
		double b;
	};
}
