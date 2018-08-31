#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>

namespace Ly {
	class CommandBuffers {
	public:
		CommandBuffers(VkDevice& device, VkCommandPool& commandPool, 
			std::vector<VkFramebuffer>& swapChainFramebuffers, 
			VkPipelineLayout& pipelineLayout, 
			VkPipeline& graphicsPipeline,
			VkRenderPass& renderPass,
			VkExtent2D& swapChainExtent,
			VkBuffer& vertexBuffer,
			VkBuffer& indexBuffer,
			uint32_t indicesSize,
			std::vector<VkDescriptorSet>& descriptorSets);
		~CommandBuffers();
		std::vector<VkCommandBuffer>& get();
		VkCommandBuffer& get(uint32_t indice);

	private:
		std::vector<VkCommandBuffer> m_commandBuffers;
		
		VkDevice& m_device;
		std::vector<VkFramebuffer>& m_swapChainFramebuffers;
		VkPipelineLayout& m_pipelineLayout;
		VkPipeline& m_graphicsPipeline;
		VkCommandPool& m_commandPool;
		VkRenderPass& m_renderPass;
		VkExtent2D& m_swapChainExtent;
		VkBuffer& m_vertexBuffer;
		VkBuffer& m_indexBuffer;
		uint32_t m_indicesSize;
		std::vector<VkDescriptorSet>& m_descriptorSets;

		void create();
	};
}
