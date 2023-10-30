#include "app.hpp"
#include "test_system.hpp"


using namespace engine;

void App::run() {

    scene.insertSystem<TestSystem>(10,20);
    scene.registerComponentList<Transform, Empty>();

    auto entity = scene.createEntity(Transform(), Empty());

    while (!glfwWindowShouldClose(window.getGLFWwindow())) {
        glfwPollEvents();

        vulkan.update();
    }
}
