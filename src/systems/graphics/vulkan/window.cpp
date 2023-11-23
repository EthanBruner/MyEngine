#include "window.hpp"

#include <stdexcept>

namespace engine {

	Window::Window(uint32_t w, uint32_t h, std::string name) : windowWidth{ w }, windowHeight { h }, windowName{name} {
		initWindow();
	};

	Window::~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}


	void Window::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Prevents creation of OpenGl context
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(int(windowWidth), int(windowHeight), windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	}


	void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto vulkanWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		vulkanWindow->framebufferResized = true;
		vulkanWindow->windowWidth = width;
		vulkanWindow->windowHeight = height;
	}
}