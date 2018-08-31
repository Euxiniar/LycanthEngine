#pragma once
#include <vulkan/vulkan.h>
#include <Buffer.h>

namespace Ly {
	class VertexBuffer : public Buffer {
	public:
		VertexBuffer(VkDevice &device,
			VkPhysicalDevice &physicalDevice,
			VkDeviceSize size);
		~VertexBuffer();
	};
}
