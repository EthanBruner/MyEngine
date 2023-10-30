#pragma once 

#include "utils.hpp"

#include <glm/glm.hpp>

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
		const char* meshPath;
		Mesh(const char* path) : meshPath{ path } {};
	};

	struct Texture : public Component<Texture> {
		const char* texturePath;
		Texture(const char* path) : texturePath{ path } {};
	};

};
