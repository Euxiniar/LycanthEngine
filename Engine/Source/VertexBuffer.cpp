#include <VertexBuffer.h>

namespace Ly {
	VertexBuffer::VertexBuffer(VkDevice& device, VkPhysicalDevice& physicalDevice, const std::vector<Vertex>& vertices)
		: m_vertices(vertices), 
		m_bufferSize(sizeof(m_vertices[0]) * m_vertices.size()), 
		Buffer(device, physicalDevice)
	{
		Buffer::create(m_bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		create();
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::create()
	{
		void* data;
		vkMapMemory(m_device, m_bufferMemory, 0, m_bufferSize, 0, &data);
		memcpy(data, m_vertices.data(), (size_t)m_bufferSize);
		vkUnmapMemory(m_device, m_bufferMemory);
	}
}