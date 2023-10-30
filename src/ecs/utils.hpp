#pragma once 

#include <glm/glm.hpp>

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
	using SystemName = const char*;


	// --- Misc. --- //
	template <typename T>
	const char* getTypeName() { return typeid(T).name(); };



	// IDK about this
	#define typelist(Name,...) \
		enum Name##Req { __VA_ARGS__ }; \
		namespace { const std::initializer_list<Name##Req> Name##List { __VA_ARGS__ }; };

	#define SysRequirementsFor(Name) \
		const std::initializer_list<Name##Req> systemRequirements = Name##List
}