#include "vulkan_system.hpp"

using namespace engine;


VulkanSystem::VulkanSystem(int windowWidth, int windowHeight, std::string windowName) : window { windowWidth, windowHeight, windowName } {

}


VulkanSystem::~VulkanSystem() {

}


void VulkanSystem::loop(std::function<void()> func) {
	while (!window.shouldClose()) {
		glfwPollEvents();
		func();
	}
	vkDeviceWaitIdle(vulkanContext.getDevice());
}

// Update will be called in the loop fucntion
void VulkanSystem::update() {

}