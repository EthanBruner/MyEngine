#include "app.hpp"

using namespace engine;

void App::run() {


    while (!glfwWindowShouldClose(window.getGLFWwindow())) {
        glfwPollEvents();
        vulkan.drawFrame();

    }

    vkDeviceWaitIdle(vulkan.device);
}
