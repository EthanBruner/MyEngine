#pragma once

#include "ecsUtils.hpp"
#include "system.hpp"

#include <unordered_map>
#include <vector>
#include <memory>

namespace engine {

	class SystemManager {
	protected:
		SystemManager() {};
		~SystemManager() {};

		template<typename T, typename... ExpectedComponents>
		void registerSystem(ExpectedComponents&&... componentTypes) {
			systems.emplace(getTypeName<T>(), std::make_unique<T>());
		}

		void update() {

		}

	private:
		std::unordered_map<SystemName, std::unique_ptr<System>> systems{};
		std::unordered_map <ComponentTypeName, std::vector<SystemName>> systemExpectations;
	};
}