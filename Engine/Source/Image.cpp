#include "Image.h"

namespace Ly {
	Image::Image(VkDevice& device, VkPhysicalDevice& physicalDevice, 
		uint32_t imageWidth, uint32_t imageHeight,
		VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, 
		VkMemoryPropertyFlags properties)
		: m_device(device), m_physicalDevice(physicalDevice)
	{
		create(imageWidth, imageHeight, format, tiling, usage, properties);
	}

	Image::~Image()
	{
		vkDestroyImage(m_device, m_image, nullptr);
		vkFreeMemory(m_device, m_imageMemory, nullptr);
	}

	VkImage& Image::get()
	{
		return m_image;
	}

	void Image::create(uint32_t imageWidth, uint32_t imageHeight,
		VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
		VkMemoryPropertyFlags properties)
	{
		VkImageCreateInfo imageInfo = {};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = imageWidth;
		imageInfo.extent.height = imageHeight;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.flags = 0;

		if (vkCreateImage(m_device, &imageInfo, nullptr, &m_image) != VK_SUCCESS) {
			Ly::Log::error("Failed to create image!");
		}

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(m_device, m_image, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = Ly::Buffer::findMemoryType(m_physicalDevice, 
			memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(m_device, &allocInfo, nullptr, &m_imageMemory) != VK_SUCCESS) {
			Ly::Log::error("Failed to allocate image memory!");
		}

		vkBindImageMemory(m_device, m_image, m_imageMemory, 0);
	}
}
