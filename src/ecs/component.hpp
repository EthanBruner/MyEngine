#pragma once 

#include "utils.hpp"

#include <glm/glm.hpp>

namespace engine {


	struct Empty {};

	struct Transform {
		glm::vec3 position;
		glm::vec3 rotation;
		float scale;


		Transform(glm::vec3 position = glm::vec3(0.f,0.f,0.f), glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), float scale = 1.0f)
			: position{ position }, rotation{ rotation }, scale{ scale }
		{};
	};

	struct Mesh {
		const char* path;
		// Insert < pointer to mesh >;
		Mesh(const char* path) : path{ path } {};
	};

	struct Texture {
		const char* path;
		// Insert < pointer to texture >;
	};

};
