#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <Swapchain.h>
#include <vector>
#include <ImageView.h>
#include <memory>

namespace Ly {
	class ImageViews {
	public:
		ImageViews(VkDevice& device,
		std::vector<VkImage>& swapChainImages,
		VkFormat& swapChainImageFormat, VkImageAspectFlags aspectFlags);
		~ImageViews();
		std::vector<std::unique_ptr<Ly::ImageView>>& get();

	private:
		std::vector<std::unique_ptr<Ly::ImageView>> m_swapChainImageViews;
		void create();

		VkDevice& m_device;
		std::vector<VkImage>& m_swapChainImages;
		VkFormat& m_swapChainImageFormat;
		VkImageAspectFlags m_aspectFlags;
	};
}
