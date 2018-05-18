#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>

namespace Ly {
	class CommandBuffers {
	public:
		CommandBuffers(VkDevice& device, VkCommandPool& commandPool, 
			std::vector<VkFramebuffer>& swapChainFramebuffers, VkPipeline& graphicsPipeline,
			VkRenderPass& renderPass,
			VkExtent2D& swapChainExtent);
		~CommandBuffers();
		std::vector<VkCommandBuffer>& get();
		VkCommandBuffer& get(uint32_t indice);

	private:
		std::vector<VkCommandBuffer> m_commandBuffers;
		
		VkDevice& m_device;
		std::vector<VkFramebuffer>& m_swapChainFramebuffers;
		VkPipeline& m_graphicsPipeline;
		VkCommandPool& m_commandPool;
		VkRenderPass& m_renderPass;
		VkExtent2D& m_swapChainExtent;

		void create();
	};
}
