#pragma once 

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <iostream>

namespace engine {

	// --- Entity --- //
	using Entity = std::size_t;
	using Index = std::size_t;
	static constexpr auto InvalidIndex = std::numeric_limits<Index>::max();

	// --- Components --- //
	using ContainerTypeName = const char*;
	using ComponentTypeName = const char*;
	using ComponentId = std::size_t;


	// --- Systems --- //
	



	// --- Misc. --- //
	template <typename T>
	const char* getTypeName() { return typeid(T).name(); }; // Gets typename of type
	template <typename T>
	const char* getTypeName(T arg) { return typeid(T).name(); }; // Gets typename of argument
}
