#include "system_mediator.hpp"

using namespace engine;


EntityComponentSystem::EntityComponentSystem() {
	componentContainerPool = std::make_shared<ContainerPool>();
	systemMediator = std::make_shared<SystemMediator>( std::make_shared<EntityComponentSystem>(*this));
};



// --- Entity Functions --- //
void EntityComponentSystem::removeEntity(Entity entity) {
	assertEntityExists(entity);

	entities.erase(std::find(entities.begin(), entities.end(), entity));
	freeEntities.emplace_back(entity);

	for (auto& [id, containerType] : entityOwnershipMap[entity]) {
		getComponentContainer(containerType)->remove(id);
		componentToEntityMap.erase(id);
	}
	entityOwnershipMap.erase(entity);
}




// --- System Functions --- //
void EntityComponentSystem::feedMainSystemLoop(std::function<void()> func) {
	std::static_pointer_cast<MainSystem>(systems[mainSys])->loop(func);
}


void EntityComponentSystem::update() {
	for (auto& [key, sys] : systems) {
		sys->update();
	}
}




// --- Private Functions --- // 
void EntityComponentSystem::assertEntityExists(Entity entity) {
	assert(std::find(entities.begin(), entities.end(), entity) != entities.end() && "EntityComponentSystemError: entity does not exist ");
}


Entity& EntityComponentSystem::findComponentOwner(ComponentId id) {
	assert(componentToEntityMap.find(id) != componentToEntityMap.end() && "EntityComponentManagerError: Cannot find the owner of an unbinded component...");
	return componentToEntityMap[id];
}




