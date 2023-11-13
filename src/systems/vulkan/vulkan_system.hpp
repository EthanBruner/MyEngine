#pragma once

#include "../../ecs/entity_component_system.hpp"
#include "../systems_utils.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "graphics_objects.hpp"
#include "utils.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace engine {

	class Vulkan: public System {
	public:

		Vulkan(std::shared_ptr<EntityComponentSystem> parentEcs, int w, int h, std::string name);
		~Vulkan();

		virtual void update();

		template<typename F>
		void loop(const F& func) {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
				func();
			}
            vkDeviceWaitIdle(device);
		}


	private:
		// Window
		int width;
		int height;
		std::string windowName;
		GLFWwindow* window;
		bool windowResized = false;

        // Vulkan-Window Interface
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;

        // Device
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;

        //Anti Aliasing
        VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

        // Image Queues
        VkQueue graphicsQueue;
        VkQueue presentQueue;

        // Swapchain
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        const int MAX_FRAMES_IN_FLIGHT = 2;

        // Graphics Pipeline
        const char* VERTEX_SHADER_PATH = "shaders/vert.spv";
        const char* FRAGMENT_SHADER_PATH = "shaders/frag.spv";
        VkRenderPass renderPass;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        
        // Commands
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        // Texture Data
        VkImage colorImage;
        VkDeviceMemory colorImageMemory;
        VkImageView colorImageView;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;

        // Buffers
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        std::vector<void*> uniformBuffersMapped;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        // Synchronization
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        uint32_t currentFrame = 0;


		void initWindow();

        void createInstance();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setupDebugMessenger();

        void createSurface();

        void pickPhysicalDevice();
        void createLogicalDevice();

        void createSwapChain();
        void cleanupSwapChain();
        void recreateSwapChain();

        void createImageViews();
        void createRenderPass();

        void createDescriptorSetLayout();
        void createGraphicsPipeline();

        void createFramebuffers();
        void createCommandPool();
        void createColorResources();
        void createDepthResources();

        void createTextureImage();
        void createTextureImageView();
        void createTextureSampler();

        void createDescriptorPool();
        void createDescriptorSets();

        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createSyncObjects();

        void createVertexBuffer();
        void createIndexBuffer();
        void createUniformBuffers();
        void updateUniformBuffer(uint32_t currentImage);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);



        // Utility Functions
        static void resizeCallback(GLFWwindow* window, int width, int height);
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
        void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        VkShaderModule createShaderModule(const std::vector<char>& code);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSampleCountFlagBits getMaxUsableSampleCount();
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        bool checkValidationLayerSupport();
	};
}