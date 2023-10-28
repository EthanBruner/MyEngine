#pragma once

#include "../../src/ecs/system.hpp"
#include "window.hpp"
#include "buffer_objects.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>


namespace engine {

    const std::string MODEL_PATH = "assests/viking_room.obj";
    const std::string TEXTURE_PATH = "assests/viking_room.png";

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif


    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


	class VulkanPipeline {
	public:
        VulkanPipeline(Window& window, const char* vertexPath, const char* fragmentPath) : window{ window } {
            createInstance();
            setupDebugMessenger();
            createSurface();
            pickPhysicalDevice();
            createLogicalDevice();
            createSwapChain();
            createImageViews();
            createRenderPass();
            createDescriptorSetLayout();
            createGraphicsPipeline(vertexPath, fragmentPath);
            createCommandPool();
            createColorResources();
            createDepthResources();
            createFramebuffers();
            createTextureImage();
            createTextureImageView();
            createTextureSampler();
            loadModel();
            createVertexBuffer();
            createIndexBuffer();
            createUniformBuffers();
            createDescriptorPool();
            createDescriptorSets();
            createCommandBuffers();
            createSyncObjects();
        };
        ~VulkanPipeline();

        VkDevice getDevice() { return device; };

        // Draws the frame
        virtual void update();

	private:
        Window& window;

        VkDevice device;

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        const int MAX_FRAMES_IN_FLIGHT = 2;

        VkRenderPass renderPass;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        VkCommandPool commandPool;

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

        std::vector<VertexObject> vertices;
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

        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        uint32_t currentFrame = 0;

        // Vulkan Initiation Functions
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
        void createGraphicsPipeline(const char* vertexPath, const char* fragmentPath);
        
        void createFramebuffers();
        void createCommandPool();
        void createColorResources();
        void createDepthResources();

        void createTextureImage();
        void createTextureImageView();
        void createTextureSampler();

        void createUniformBuffers();
        void updateUniformBuffer(uint32_t currentImage);

        void createDescriptorPool();
        void createDescriptorSets();


        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createSyncObjects();

        void loadModel();

        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void createVertexBuffer();
        void createIndexBuffer();
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);



        // Vulkan Helper Functions
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

        VkSampleCountFlagBits getMaxUsableSampleCount();

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

        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        bool checkValidationLayerSupport();

        static std::vector<char> readFile(const std::string& filename);

	};
}