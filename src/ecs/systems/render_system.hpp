#pragma once

#include "../system.hpp"

namespace engine {

	// Should handle the passing of entity graphics data to the graphics api
	class RenderSystem: public System {
	public:
		RenderSystem() {};
		~RenderSystem() {};

		virtual void update(std::shared_ptr<ContainerPool> containerPool) {
		}
		
	private:
	};

}