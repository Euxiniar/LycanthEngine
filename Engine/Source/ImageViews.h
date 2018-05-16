#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <Swapchain.h>
#include <vector>

namespace Ly {
	class ImageViews {
	public:
		ImageViews(VkDevice& device,
		std::vector<VkImage>& swapChainImages,
		VkFormat& swapChainImageFormat);
		~ImageViews();
	private:
		std::vector<VkImageView> m_swapChainImageViews;
		void createImageViews();

		VkDevice& m_device;
		std::vector<VkImage>& m_swapChainImages;
		VkFormat& m_swapChainImageFormat;
	};
}
