#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <Buffer.h>

namespace Ly {
	class Image {
	public:
		Image(VkDevice& device, VkPhysicalDevice& physicalDevice, uint32_t texWidth, uint32_t texHeight);
		~Image();
		VkImage& get();
	private:
		VkImage m_image;
		VkDeviceMemory m_imageMemory;
		VkDevice& m_device;
		VkPhysicalDevice& m_physicalDevice;

		void create(uint32_t texWidth, uint32_t texHeight);
	};
}