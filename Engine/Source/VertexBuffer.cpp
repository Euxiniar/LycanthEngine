#include "VertexBuffer.h"

Ly::VertexBuffer::VertexBuffer(VkDevice & device, 
	VkPhysicalDevice & physicalDevice, 
	VkDeviceSize size,
	void* data) :
	Buffer(device, 
		physicalDevice, 
		size, 
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | 
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
	m_data(data)
{
	create();
}

Ly::VertexBuffer::~VertexBuffer()
{
}

void Ly::VertexBuffer::create()
{
	/*void* data;
	vkMapMemory(m_device, m_bufferMemory, 0, m_bufferSize, 0, &data);
	memcpy(data, m_data, (size_t) m_bufferSize);
	vkUnmapMemory(m_device, m_bufferMemory);*/
}
