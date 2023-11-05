#pragma once 

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <iostream>

namespace engine {

	// --- Entity --- //
	using Entity = std::size_t;

	// --- Components --- //
	using ContainerTypeName = const char*;
	using ComponentTypeName = const char*;
	using ComponentId = std::size_t;

	// --- Systems --- //
	using SystemTypeName = const char*;


	// --- Misc. --- //
	template <typename T>
	const char* getTypeName() { return typeid(T).name(); }; // Gets typename of type
	template <typename T>
	const char* getTypeName(T arg) { return typeid(T).name(); }; // Gets typename of argument
}
