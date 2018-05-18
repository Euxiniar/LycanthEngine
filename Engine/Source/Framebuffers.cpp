#include "Framebuffers.h"

namespace Ly {
	Framebuffers::Framebuffers(VkDevice & device,
		std::vector<VkImageView>& swapChainImageViews,
		VkRenderPass & renderPass, VkExtent2D & swapChainExtent)
		: m_device(device), m_swapChainImageViews(swapChainImageViews),
		m_renderPass(renderPass), m_swapChainExtent(swapChainExtent)
	{
		create();
	}

	Framebuffers::~Framebuffers()
	{
		for (auto framebuffer : m_swapChainFramebuffers) {
			vkDestroyFramebuffer(m_device, framebuffer, nullptr);
		}
	}

	std::vector<VkFramebuffer>& Framebuffers::get()
	{
		return m_swapChainFramebuffers;
	}

	void Framebuffers::create()
	{
		m_swapChainFramebuffers.resize(m_swapChainImageViews.size());

		for (size_t i = 0; i < m_swapChainImageViews.size(); i++) {
			VkImageView attachments[] = {
				m_swapChainImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = m_swapChainExtent.width;
			framebufferInfo.height = m_swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS) {
				Ly::Log::error("Failed to create framebuffer!");
			}
		}
	}
}