#pragma once

#include "window.hpp"

#include <vulkan/vulkan.hpp>

// std lib headers
#include <string>
#include <vector>

namespace engine {

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
  uint32_t graphicsFamily;
  uint32_t presentFamily;
  bool graphicsFamilyHasValue = false;
  bool presentFamilyHasValue = false;

  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};



// Handles the initialization of a vulkan instance and acts as the iterface to the graphics device
class VulkanCoreConstruct {
 public:
	#ifdef NDEBUG
	const bool enableValidationLayers = false;
	#else
	const bool enableValidationLayers = true;
	#endif

  VulkanCoreConstruct(Window &window);
  ~VulkanCoreConstruct();

  VulkanCoreConstruct(const VulkanCoreConstruct &) = delete;
  void operator=(const VulkanCoreConstruct &) = delete;
  VulkanCoreConstruct(VulkanCoreConstruct &&) = delete;
  VulkanCoreConstruct &operator=(VulkanCoreConstruct &&) = delete;


  // --- Getter Fuctions --- //
  VkSurfaceKHR getSurface() { return surface; }
  VkCommandPool getCommandPool() { return commandPool; }
  VkDevice getDevice() const { return device; }
  VkQueue getGraphicsQueue() { return graphicsQueue; }
  VkQueue getPresentQueue() { return presentQueue; }
  SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }

  // --- Infomation  --- //
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }
  VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

  // --- Commands --- //
  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);

  // --- Buffers --- //
  void createBuffer( VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

  // --- Image --- //
  void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);


private:
	Window &window;

	VkInstance instance;
	VkSurfaceKHR surface;
	VkDebugUtilsMessengerEXT debugMessenger;
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };


	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkPhysicalDeviceProperties properties;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkCommandPool commandPool;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexMemory;

	VkBuffer indexBuffer;
	VkDeviceMemory indexMemory;


	void createInstance();
	void setupDebugMessenger();
	void createSurface();

	void pickPhysicalDevice();
	void createLogicalDevice();

	void createCommandPool();

	void createMemoryBuffers();

	// helper functions
	void freeBuffer(VkBuffer buffer, VkDeviceMemory memory);

	bool isDeviceSuitable(VkPhysicalDevice device);
	std::vector<const char *> getRequiredExtensions();
	bool checkValidationLayerSupport();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
	void hasGflwRequiredInstanceExtensions();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
};

}