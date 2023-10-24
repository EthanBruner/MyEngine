#pragma once 

#include "ecsUtils.hpp"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>
#include <typeinfo>


namespace engine {

	// NOTE: component<T> likly no longer needs to store its id as it's being managed by the EntityComponentManager
	template<typename T>
	struct Component {
	public:

		void setId(ComponentId componentIdNumber) {
			if (idHasBeenSet) {
				throw std::runtime_error("ComponentError: Cannot use setId() on a component multiple times...");
			}
			else {
				id = componentIdNumber;
				idHasBeenSet = false;
			}
		};

		ComponentId& getId() { return id; };

	private:
		ComponentId id = 0;
		bool idHasBeenSet = false;
	};



	struct Transform : public Component<Transform> {
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		float scale;


		Transform(glm::vec3 position = glm::vec3(0.f,0.f,0.f), glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), float scale = 1.0f)
			: position{ position }, rotation{ rotation }, scale{ scale }
		{};
	};


	struct Empty : public Component<Empty> {
		void* null;
	};

};
