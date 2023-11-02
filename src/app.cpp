#include "app.hpp"


using namespace engine;

void App::run() {

    scene.insertSystem<VulkanSystem>(800, 600, "Application Window Name");

    
    // Main Application Loop
    auto mainLoop = [&]() {
        scene.update();

    };
    scene.getSystem<VulkanSystem>()->loop(mainLoop);
}
