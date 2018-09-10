#pragma once
#include <vulkan\vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class ImageView {
	public:
		ImageView(VkDevice& device, VkImage& image, VkFormat format, VkImageAspectFlags aspectFlags);
		~ImageView();
		VkImageView& get();

	private:
		VkImageView m_imageView;
		VkDevice& m_device;
		VkImage& m_image;
		VkFormat m_format;
		VkImageAspectFlags m_aspectFlags;

		void create();
	};
}