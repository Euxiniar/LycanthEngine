#pragma once
#include <Utils/Log.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <ImageView.h>

namespace Ly {
	class Framebuffers {
	public :
		Framebuffers(VkDevice& device,
			std::vector<std::unique_ptr<Ly::ImageView>>& swapChainImageViews,
			VkRenderPass& renderPass,
			VkExtent2D& swapChainExtent);
		~Framebuffers();

		std::vector<VkFramebuffer>& get();

	private:
		VkDevice & m_device;
		std::vector<std::unique_ptr<Ly::ImageView>>& m_swapChainImageViews;
		VkRenderPass& m_renderPass;
		VkExtent2D& m_swapChainExtent;

		std::vector<VkFramebuffer> m_swapChainFramebuffers;
		void create();
	};
}
