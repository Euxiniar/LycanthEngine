#include "IndexBuffer.h"

namespace Ly {

	IndexBuffer::IndexBuffer(VkDevice &device, 
		VkPhysicalDevice &physicalDevice, 
		VkDeviceSize size) :
		Buffer(device, 
			physicalDevice, 
			size, 
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | 
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{
	}

	IndexBuffer::~IndexBuffer()
	{

	}

}