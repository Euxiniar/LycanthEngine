#pragma once
#include <Utils/Log.h>
#include <vulkan/vulkan.h>
#include <vector>

namespace Ly {
	class Framebuffers {
	public :
		Framebuffers(VkDevice& device,
			std::vector<VkImageView>& swapChainImageViews,
			VkRenderPass& renderPass,
			VkExtent2D& swapChainExtent);
		~Framebuffers();

	private:
		VkDevice & m_device;
		std::vector<VkImageView>& m_swapChainImageViews;
		VkRenderPass& m_renderPass;
		VkExtent2D& m_swapChainExtent;

		std::vector<VkFramebuffer> m_swapChainFramebuffers;
		void create();
	};
}
