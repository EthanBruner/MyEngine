#pragma once

#include "ecsUtils.hpp"
#include "component.hpp"

#include <vector>
#include <utility>

namespace engine {


	class BaseComponentContainer {};

	template<typename T>
	class ComponentContainer : public BaseComponentContainer {
	public:
		ComponentContainer() {};

		void add(ComponentId id, Component<T> component) {
			components.emplace(id, component);
		};

		void remove(ComponentId id) {
			components.erase(id);
		};

	private:
		std::unordered_map<ComponentId, Component<T>> components;
		
	};
};