#pragma once

#include <memory>

namespace engine {
	
	class EntityComponentSystem;

	class System {
	public:
		System(std::shared_ptr<EntityComponentSystem> parentEcs) : ecs{ parentEcs } {};
		virtual void update() = 0;
	protected:
		// NOTE: ecs fuctions cannot be called inside System because they dont exist yet
		std::shared_ptr<engine::EntityComponentSystem> ecs;
	};

}