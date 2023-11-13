#include "app.hpp"
using namespace engine;

#include <GLFW/glfw3.h>


void App::run() {

    scene.registerComponents<Mesh, Texture, Transform>();

    scene.createEntity(Mesh("assests/viking_room.obj"), Texture("assests/viking_room.png"), Transform());

    scene.insertSystem<ResourceManager>();
    scene.insertSystem<Vulkan>(800, 600, "Default Window");

    auto mainLoop = [&]() {
        scene.update();
    };
    scene.getSystem<Vulkan>()->loop(mainLoop);
}
