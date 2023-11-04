#include "resource_manager.hpp"
using namespace engine;

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>


void ResourceManager::init(std::shared_ptr<ContainerPool> container_pool , std::vector<std::shared_ptr<System>> system_pool) {
    containerPool = container_pool;
    setSystemPool(system_pool);

	auto& compoents = retrieve<Mesh>(containerPool);
	for (auto&[id, mesh] : compoents) {
		loadObj(mesh.path);
	}
};


void ResourceManager::loadObj(const char* model_path) {

    // If the model has already been loaded return early
    if (meshes.find(model_path) != meshes.end()) {
        return;
    }

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, model_path)) {
        throw std::runtime_error(warn + err);
    }

    MeshObj newMesh {};
    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Create Vertex 
            Vertex vertex{};
            vertex.pos = {
                attrib.vertices[3 * size_t(index.vertex_index) + 0],
                attrib.vertices[3 * size_t(index.vertex_index) + 1],
                attrib.vertices[3 * size_t(index.vertex_index) + 2]
            };
            
            vertex.normal = {
                attrib.normals[3 * size_t(index.normal_index) + 0],
                attrib.normals[3 * size_t(index.normal_index) + 1],
                attrib.normals[3 * size_t(index.normal_index) + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * size_t(index.texcoord_index) + 0],
                1.0f - attrib.texcoords[2 * size_t(index.texcoord_index) + 1]
            };

            vertex.color = { 
                attrib.colors[3 * size_t(index.vertex_index) + 0],
                attrib.colors[3 * size_t(index.vertex_index) + 1],
                attrib.colors[3 * size_t(index.vertex_index) + 2]
            };


            // Create Indices 
            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(newMesh.vertices.size());
                newMesh.vertices.push_back(vertex);
            }

            newMesh.indices.push_back(uniqueVertices[vertex]);
        }
    }

    meshes.emplace(model_path, newMesh);
}