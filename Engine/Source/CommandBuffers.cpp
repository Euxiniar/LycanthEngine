#include <CommandBuffers.h>

namespace Ly {
	CommandBuffers::CommandBuffers(VkDevice & device, VkCommandPool commandPool, 
		std::vector<VkFramebuffer>& swapChainFramebuffers, 
		VkPipeline & graphicsPipeline, VkRenderPass& renderPass,
		VkExtent2D& swapChainExtent)
		: m_device(device), m_commandPool(commandPool), 
		m_swapChainFramebuffers(swapChainFramebuffers), 
		m_graphicsPipeline(graphicsPipeline),
		m_renderPass(renderPass), m_swapChainExtent(swapChainExtent)
	{
	}

	CommandBuffers::~CommandBuffers()
	{
	}

	std::vector<VkFramebuffer>& CommandBuffers::get()
	{
		return m_swapChainFramebuffers;
	}
	void CommandBuffers::create()
	{
		m_commandBuffers.resize(m_swapChainFramebuffers.size());

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

		if (vkAllocateCommandBuffers(m_device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
			Ly::Log::error("Failed to allocate command buffers!");
		}

		for (size_t i = 0; i < m_commandBuffers.size(); i++) {
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			if (vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo) != VK_SUCCESS) {
				Ly::Log::error("Failed to begin recording command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = m_renderPass;
			renderPassInfo.framebuffer = m_swapChainFramebuffers[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = m_swapChainExtent;

			VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);

			vkCmdDraw(m_commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(m_commandBuffers[i]);

			if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS) {
				Ly::Log::error("Failed to record command buffer!");
			}
		}
	}
}
