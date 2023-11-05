#include "app.hpp"
using namespace engine;



void App::run() {

    scene.registerComponent<Mesh>();
    scene.registerComponent<Transform>();

    scene.createEntity(Mesh("assests/viking_room.obj"), Transform());

    scene.insertSystem<ResourceManager>();
    scene.insertSystem<VulkanSystem>(800, 600, "Default Vulkan Window");


    auto mainLoop = [&]() {
        scene.update();
    };
    scene.getSystem<VulkanSystem>()->loop(mainLoop);
}
