#include "Framebuffers.h"

namespace Ly {
	Framebuffers::Framebuffers(VkDevice & device,
		std::vector<std::unique_ptr<Ly::ImageView>>& swapChainImageViews,
		VkRenderPass & renderPass, VkExtent2D & swapChainExtent, 
		VkImageView& depthImageView)
		: m_device(device), m_swapChainImageViews(swapChainImageViews),
		m_renderPass(renderPass), m_swapChainExtent(swapChainExtent),
		m_depthImageView(depthImageView)
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
			std::array<VkImageView, 2> attachments = {
				m_swapChainImageViews[i]->get(),
				m_depthImageView
			};

			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_renderPass;
			framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = m_swapChainExtent.width;
			framebufferInfo.height = m_swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS) {
				Ly::Log::error("Failed to create framebuffer!");
			}
		}
	}
}