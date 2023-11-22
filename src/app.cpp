#include "app.hpp"
using namespace engine;

#include <GLFW/glfw3.h>


void App::run() {

    scene.registerComponents<Mesh, Texture, Transform>();

    scene.createEntity(Mesh("assests/viking_room.obj"), Texture("assests/viking_room.png"), Transform());

    scene.setMainSystem<VulkanSystem>(800, 600, "A Vulkan Window");


    auto mainLoop = [&]() {
        scene.update();
    };
    scene.feedMainSystemLoop(mainLoop);
}
