#include "vulkan_system.hpp"
using namespace engine;


void VulkanSystem::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Prevents creation of OpenGl context

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
}


void VulkanSystem::resizeCallback(GLFWwindow* window, int width, int height) {
	auto vulkanWindow = reinterpret_cast<VulkanSystem*>(glfwGetWindowUserPointer(window));
	vulkanWindow->windowResized = true;
	vulkanWindow->width = width;
	vulkanWindow->height = height;
}