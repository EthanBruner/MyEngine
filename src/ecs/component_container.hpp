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



	class ComponentContainerCollection {
	public:
		std::unordered_map<ContainerTypeName, std::shared_ptr<BaseComponentContainer>> collection;


	private:
	};
};