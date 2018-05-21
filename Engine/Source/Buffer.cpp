#include <Buffer.h>

namespace Ly {
	Buffer::Buffer(VkDevice& device, VkPhysicalDevice& physicalDevice)
		: m_device(device), m_physicalDevice(physicalDevice)
	{
	}

	Buffer::~Buffer()
	{
		vkDestroyBuffer(m_device, m_buffer, nullptr);
		vkFreeMemory(m_device, m_bufferMemory, nullptr);
	}

	VkBuffer & Buffer::get()
	{
		return m_buffer;
	}

	void Buffer::create(VkDeviceSize size, VkBufferUsageFlags usage, 
		VkMemoryPropertyFlags properties)
	{
		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(m_device, &bufferInfo, nullptr, &m_buffer) != VK_SUCCESS) {
			Ly::Log::error("Failed to create buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(m_device, m_buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(m_device, &allocInfo, nullptr, &m_bufferMemory) != VK_SUCCESS) {
			Ly::Log::error("Failed to allocate buffer memory!");
		}

		vkBindBufferMemory(m_device, m_buffer, m_bufferMemory, 0);
	}

	uint32_t Buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && 
				(memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		Ly::Log::error("Failed to find suitable memory type!");
		return std::numeric_limits<uint32_t>::max();
	}
}