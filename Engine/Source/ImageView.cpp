#include "ImageView.h"

namespace Ly {

	ImageView::ImageView(VkDevice& device, VkImage& image, VkFormat format, VkImageAspectFlags aspectFlags) : 
		m_device(device), m_image(image), m_format(format), m_aspectFlags(aspectFlags)
	{
		create();
	}

	ImageView::~ImageView()
	{
		vkDestroyImageView(m_device, m_imageView, nullptr);
	}

	VkImageView & ImageView::get()
	{
		return m_imageView;
	}

	void ImageView::create()
	{
		VkImageViewCreateInfo viewInfo = {};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = m_image;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = m_format;
		viewInfo.subresourceRange.aspectMask = m_aspectFlags;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(m_device, &viewInfo, nullptr, &m_imageView) != VK_SUCCESS) {
			Ly::Log::error("Failed to create texture image view!");
		}
	}
}