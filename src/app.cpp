#include "app.hpp"
using namespace engine;



void App::run() {

    // Register Scene Components 
    scene.registerComponent<Mesh>();
    scene.registerComponent<Transform>();

    // Create Entities
    scene.createEntity(Mesh("assests/viking_room.obj"), Transform());
    scene.createEntity(Mesh("assests/viking_room.obj"), Transform());


    scene.insertSystem<ResourceManager>();
    scene.insertSystem<VulkanSystem>(800, 600, "Default Vulkan Window");

    scene.init();
    auto mainLoop = [&]() {
        scene.update();
    };
    scene.getSystem<VulkanSystem>()->loop(mainLoop);
}
