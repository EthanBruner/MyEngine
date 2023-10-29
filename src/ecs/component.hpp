#pragma once 

#include "utils.hpp"
#include "systems/graphics_objects.hpp"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>
#include <typeinfo>


namespace engine {

	template<typename T>
	struct Component {};

	struct Empty : public Component<Empty> {};


	struct Transform : public Component<Transform> {
		glm::vec3 position;
		glm::vec3 rotation;
		float scale;


		Transform(glm::vec3 position = glm::vec3(0.f,0.f,0.f), glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), float scale = 1.0f)
			: position{ position }, rotation{ rotation }, scale{ scale }
		{};
	};


	struct Mesh : public Component<Mesh> {
		std::vector<Vertex> vertices;
		std::vector<int> indices;
	};



};
