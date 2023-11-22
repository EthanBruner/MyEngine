#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <tuple>

namespace engine {

	class Window {
	public:
		Window(uint32_t w, uint32_t h, std::string name);
		~Window();
		// Delete copy constructor and copy operator
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		uint32_t width() { return windowWidth; };
		uint32_t height() { return windowHeight; };
		GLFWwindow* getWindow() const { return window; }

		bool shouldClose() { return glfwWindowShouldClose(window); }
		bool wasWindowResized() {return framebufferResized; }
		void resetWindowResizedFlag() { framebufferResized = false; }
		
	private:
		uint32_t windowWidth;
		uint32_t windowHeight;
		std::string windowName;

		GLFWwindow *window;
		bool framebufferResized = false;

		void initWindow();

		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	};
}
