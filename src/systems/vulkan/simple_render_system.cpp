#include "simple_render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>
#include <array>

namespace engine {

	struct SimplePushConstantData {
		glm::mat4 transfrom{ 1.f };
		glm::mat4 modelMatrix;
	};



	SimpleRenderSystem::SimpleRenderSystem(VulkanCoreContext& vulkanContext, RenderPass& renderPass) : device{ vulkanContext.getDevice() } {
		createPipelineLayout();
		createPipeline(renderPass);
	}


	SimpleRenderSystem::~SimpleRenderSystem() {
		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
	}



	void SimpleRenderSystem::createPipelineLayout() {

		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(SimplePushConstantData);

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

		if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create pipeline layout!");
		}
	};


	void SimpleRenderSystem::createPipeline(RenderPass& renderPass) {
		PipelineConfigInfo pipelineConfig{};
		VulkanPipeline::defaultConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = &renderPass;
		pipelineConfig.pipelineLayout = pipelineLayout;

		vulkanPipeline = std::make_unique<VulkanPipeline>( device, "shaders/simple.vert.spv", "shaders/simple.frag.spv", pipelineConfig);
	};


	//void SimpleRenderSystem::renderObjects(VkCommandBuffer commandBuffer, std::vector<Object>& objects, const Camera& camera) {
	//	vulkanPipeline->bind(commandBuffer);

	//	auto projectionView = camera.getProjection() * camera.getView();

	//	for (auto& obj : objects) {
	//		SimplePushConstantData push{};
	//		auto modelMatrix = obj.transform.mat4();
	//		push.transfrom = projectionView * modelMatrix;
	//		push.modelMatrix = modelMatrix;

	//		vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SimplePushConstantData), &push);
	//		obj.model->bind(commandBuffer);
	//		obj.model->draw(commandBuffer);
	//	}

	//}


}