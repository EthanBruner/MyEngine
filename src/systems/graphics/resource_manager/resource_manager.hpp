#pragma once


#include "../../../ecs/system.hpp"
#include "../../systems_utils.hpp"
#include "../graphics_objects.hpp"

namespace engine {

	using mesh_path = const char*;

	class ResourceManager: public System {
	public:
		virtual void init(std::shared_ptr<ContainerPool> container_pool, std::vector<std::shared_ptr<System>> system_pool);

		virtual std::size_t size() { return sizeof(ResourceManager); };

		std::unordered_map<mesh_path, MeshObj>& getLoadedMeshes() { return meshes; }

	private:
		std::unordered_map<mesh_path, MeshObj> meshes;

		void loadObj(const char* path);
	};
}