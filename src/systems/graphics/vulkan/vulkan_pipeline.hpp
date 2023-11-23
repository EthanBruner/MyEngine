#pragma once

#include "vulkan_core_context.hpp"
#include "render_pass.hpp"
#include "graphics_objects.hpp"

#include <string>
#include <vector>

namespace engine {

	struct PipelineConfigInfo {
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo) = delete;

		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;

		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;

		VkRenderPass renderPass = nullptr;
		VkPipelineLayout pipelineLayout = nullptr;
		uint32_t subpassCount = 0;
	};


	class VulkanPipeline {
	public:
		VulkanPipeline(VkDevice device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);

		~VulkanPipeline();

		VulkanPipeline(const VulkanPipeline&) = delete;
		VulkanPipeline& operator=(const VulkanPipeline) = delete;

		void bind(VkCommandBuffer commandBuffer);

		static void defaultConfigInfo(PipelineConfigInfo& configInfo);

	private:
		VkDevice device;

		VkDescriptorSetLayout descriptorSetLayout;

		VkShaderModule vertShaderMoudule;
		VkShaderModule fragShaderMoudule;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		void createDescriptorSetLayout();
		void createVulkanPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
		
		VkShaderModule createShaderModule(const std::vector<char>& code);
		static std::vector<char> readFile(const std::string& filepath);


		

	};
}