#pragma once

#include "ecsUtils.hpp"
#include "system.hpp"

#include <any>
#include <iostream>
#include <vector>
#include <memory>

namespace engine {

	class SystemManager {
	protected:
		SystemManager() {};
		~SystemManager() {};

		template <typename T, typename... Args>
		void insertSystem(Args... args) {
			auto system = std::static_pointer_cast<System>(std::make_shared<T>(std::forward<Args>(args)...));
			systems.emplace_back(system);
		}

		void update() {
			for (auto& sys : systems) {
				sys->update();
			}
		}

	private:
		std::vector<std::shared_ptr<System>> systems{};
	};
}