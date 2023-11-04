#pragma once

#include "utils.hpp"
#include "component.hpp"

//#include <utility>
#include <memory>
#include <unordered_map>
#include <iterator>

namespace engine {

	class BaseComponentContainer {};
	using ContainerPool = std::unordered_map<ContainerTypeName, std::shared_ptr<BaseComponentContainer>>; // NOTE:: Make class ?

	template<typename T>
	using ComponentMap = std::unordered_map<ComponentId, T>;



	template<typename T>
	class ComponentContainer : public BaseComponentContainer {
	public:
		ComponentContainer() {};

		void add(ComponentId id, T component) {
			components.emplace(id, component);
		};

		void remove(ComponentId id) {
			components.erase(id);
		};

		ComponentMap<T>& getComponents() {
			return components;
		}

	private:
		ComponentMap<T> components;
		
	};
}