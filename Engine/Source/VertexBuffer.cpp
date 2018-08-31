#include "VertexBuffer.h"

Ly::VertexBuffer::VertexBuffer(VkDevice & device, 
	VkPhysicalDevice & physicalDevice, 
	VkDeviceSize size) :
	Buffer(device, 
		physicalDevice, 
		size, 
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | 
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
{

}

Ly::VertexBuffer::~VertexBuffer()
{
}
