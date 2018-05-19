#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <Vertex.hpp>
#include <vector>

namespace Ly {
	class CommandBuffers {
	public:
		CommandBuffers(VkDevice& device, VkCommandPool& commandPool, 
			std::vector<VkFramebuffer>& swapChainFramebuffers, VkPipeline& graphicsPipeline,
			VkRenderPass& renderPass,
			VkExtent2D& swapChainExtent,
			VkBuffer& vertexBuffer,
		const std::vector<Ly::Vertex>& vertices);
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
		VkBuffer& m_vertexBuffer;
		const std::vector<Ly::Vertex>& m_vertices;

		void create();
	};
}
