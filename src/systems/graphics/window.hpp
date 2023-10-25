#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

namespace engine {
	class Window {
	public:
		Window(int w, int h, std::string name);
		~Window();

		bool shouldClose() { return glfwWindowShouldClose(window); }

		bool wasWindowResized() { return framebufferResized; }
		void resetWindowResizedFlag() { framebufferResized = false; }

		VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		GLFWwindow* getGLFWwindow() const { return window; }
		void setFramebufferResized(bool value) { framebufferResized = value; }

		// Delete copy constructor and copy operator
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;


	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);


		void initWindow();

		int width;
		int height;
		bool framebufferResized = false;

		std::string windowName;
		GLFWwindow* window;
	};
}