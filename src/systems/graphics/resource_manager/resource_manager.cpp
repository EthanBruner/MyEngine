#include "resource_manager.hpp"
using namespace engine;

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>


void ResourceManager::init() {
	auto& compoents = ecs->retrieveComponents<Mesh>();
	for (auto&[id, mesh] : compoents) {
		loadObj(mesh.path);
	}
};


void ResourceManager::loadObj(const char* model_path) {

     //If the model has already been loaded return early
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

    MeshObj newMesh{};
    newMesh.vertexStart = vertices.size() + 1;
    newMesh.indexStart = indices.size() + 1;

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
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.emplace_back(vertex);
            }

            indices.emplace_back(uniqueVertices[vertex]);
        }
    }

    newMesh.vertexEnd = vertices.size();
    newMesh.indexEnd = indices.size();
    meshes.emplace(model_path, newMesh);
}