#pragma once

#include "../../../ecs/entity_component_system.hpp"
#include "../../systems_utils.hpp"
#include "../graphics_objects.hpp"

#include <tuple>

namespace engine {

	using mesh_path = const char*;

	class ResourceManager: public System {
	public:
		virtual void init();
		virtual std::size_t size() { return sizeof(ResourceManager); };


		std::tuple<std::unordered_map<mesh_path, MeshObj>&,  std::vector<Vertex>&, std::vector<uint32_t>&> getLoadedMeshData() {
			return { meshes, vertices, indices };
		}

	private:
		std::unordered_map<mesh_path, MeshObj> meshes;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		void loadObj(const char* path);
	};
}