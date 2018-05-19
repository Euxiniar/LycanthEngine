#include <VertexBuffer.h>

namespace Ly {
	VertexBuffer::VertexBuffer(VkDevice& device, VkPhysicalDevice& physicalDevice, const std::vector<Vertex>& vertices)
		: m_device(device),m_physicalDevice(physicalDevice), m_vertices(vertices)
	{
		create();
	}

	VertexBuffer::~VertexBuffer()
	{
		vkDestroyBuffer(m_device, m_vertexBuffer, nullptr);
		vkFreeMemory(m_device, m_vertexBufferMemory, nullptr);
	}

	VkBuffer & VertexBuffer::get()
	{
		return m_vertexBuffer;
	}

	void VertexBuffer::create()
	{
		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = sizeof(m_vertices[0]) * m_vertices.size();
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(m_device, &bufferInfo, nullptr, &m_vertexBuffer) != VK_SUCCESS) {
			Ly::Log::error("Failed to create vertex buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(m_device, m_vertexBuffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, 
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(m_device, &allocInfo, nullptr, &m_vertexBufferMemory) != VK_SUCCESS) {
			Ly::Log::error("Failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(m_device, m_vertexBuffer, m_vertexBufferMemory, 0);

		void* data;
		vkMapMemory(m_device, m_vertexBufferMemory, 0, bufferInfo.size, 0, &data);
		memcpy(data, m_vertices.data(), (size_t)bufferInfo.size);
		vkUnmapMemory(m_device, m_vertexBufferMemory);
	}

	uint32_t VertexBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		Ly::Log::error("Failed to find suitable memory type!");
		return std::numeric_limits<uint32_t>::max();
	}
}