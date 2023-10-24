#include "app.hpp"

#include <iostream>

using namespace engine;

void App::run() {

    scene.registerComponent<Transform>();
    scene.registerComponent<Empty>();

    auto entity = scene.createEntity(Transform(), Transform(), Empty());

    while (!glfwWindowShouldClose(window.getGLFWwindow())) {
        glfwPollEvents();
        vulkan.drawFrame();

    }

    vkDeviceWaitIdle(vulkan.getDevice());
}
