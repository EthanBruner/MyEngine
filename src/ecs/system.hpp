#pragma once

#include <memory>
#include <functional>

namespace engine {
	
	class SystemMediator;

	class System {
	public:

		void bindMediator(std::shared_ptr<SystemMediator> sysMediator) {
			mediator = sysMediator;
		}

		virtual void update() = 0;

	protected:
		std::shared_ptr<SystemMediator> mediator;
	};

	

	class MainSystem : public System {
	public:
		virtual void loop(std::function<void()> func) = 0;
	};

}