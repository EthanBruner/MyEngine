#pragma once

#include "vulkan_core_context.hpp"

// vulkan headers
#include <vulkan/vulkan.h>

// std lib headers
#include <memory>
#include <string>
#include <vector>

namespace engine {

    class VulkanSwapChain {
    public:
        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

        VulkanSwapChain(VulkanCoreConstruct& vulkanContext, Window& window);
        VulkanSwapChain(VulkanCoreConstruct& vulkanContext, Window& window, std::shared_ptr<VulkanSwapChain> previous);
        ~VulkanSwapChain();

        VulkanSwapChain(const VulkanSwapChain&) = delete;
        void operator=(const VulkanSwapChain&) = delete;

        VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
        VkRenderPass getRenderPass() { return firstPass; }
        VkImageView getImageView(int index) { return swapChainImageViews[index]; }
        size_t imageCount() { return swapChainImages.size(); }
        VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
        VkExtent2D getSwapChainExtent() { return swapChainExtent; }
        uint32_t width() { return swapChainExtent.width; }
        uint32_t height() { return swapChainExtent.height; }

        float extentAspectRatio() {
            return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
        }
        VkFormat findDepthFormat();

        VkResult acquireNextImage(uint32_t* imageIndex);
        VkResult submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);

        bool compareSwapFormats(const VulkanSwapChain& swapChain) const {
            return swapChain.swapChainDepthFormat == swapChainDepthFormat && swapChain.swapChainImageFormat == swapChainImageFormat;
        }

    private:
        VulkanCoreConstruct& vulkanContext;
        VkExtent2D windowExtent;

        VkSwapchainKHR swapChain;
        std::shared_ptr<VulkanSwapChain> oldSwapChain;

        VkFormat swapChainImageFormat;
        VkFormat swapChainDepthFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkRenderPass firstPass;
        VkRenderPass secondPass;
        VkSampleCountFlagBits msaaSampleCount = VK_SAMPLE_COUNT_4_BIT;

        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkImage> depthImages;
        std::vector<VkDeviceMemory> depthImageMemorys;
        std::vector<VkImageView> depthImageViews;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;


        void init();
        void createSwapChain();
        void createImageViews();
        void createDepthResources();

        void createRenderPass(VkRenderPass& renderPass);

        void createFramebuffers();
        void createSyncObjects();

        // Helper functions
        VkSurfaceFormatKHR chooseSwapSurfaceFormat( const std::vector<VkSurfaceFormatKHR>& availableFormats );
        VkPresentModeKHR chooseSwapPresentMode( const std::vector<VkPresentModeKHR>& availablePresentModes );
        VkExtent2D chooseSwapExtent( const VkSurfaceCapabilitiesKHR& capabilities );

    };

}