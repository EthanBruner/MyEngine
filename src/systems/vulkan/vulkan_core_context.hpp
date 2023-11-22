#pragma once

#include "window.hpp"
//#include "swap_chain.hpp"

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


class VulkanCoreContext {
 public:
  #ifdef NDEBUG
  const bool enableValidationLayers = false;
  #else
  const bool enableValidationLayers = true;
  #endif

  VulkanCoreContext(Window &window);
  ~VulkanCoreContext();

  VulkanCoreContext(const VulkanCoreContext &) = delete;
  void operator=(const VulkanCoreContext &) = delete;
  VulkanCoreContext(VulkanCoreContext &&) = delete;
  VulkanCoreContext &operator=(VulkanCoreContext &&) = delete;


  // --- Getter Fuctions --- //
  VkCommandPool getCommandPool() { return commandPool; }
  VkDevice getDevice() const { return device; }
  VkSurfaceKHR getSurface() { return surface; }
  VkQueue getGraphicsQueue() { return graphicsQueue; }
  VkQueue getPresentQueue() { return presentQueue; }

  // --- Infomation  --- //
  SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }
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
	const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
	const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	Window &window;
	VkInstance instance;
	VkSurfaceKHR surface;
	VkDebugUtilsMessengerEXT debugMessenger;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkPhysicalDeviceProperties properties;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkCommandPool commandPool;

	void createInstance();
	void setupDebugMessenger();
	void createSurface();

	void pickPhysicalDevice();
	void createLogicalDevice();

	void createCommandPool();

	// helper functions
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