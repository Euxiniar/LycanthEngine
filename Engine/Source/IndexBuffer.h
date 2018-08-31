#pragma once
#include <vulkan/vulkan.h>
#include <Buffer.h>

namespace Ly {
	class IndexBuffer : public Buffer{
	public :
		IndexBuffer(VkDevice &device,
			VkPhysicalDevice &physicalDevice,
			VkDeviceSize size);
		~IndexBuffer();
	};
}