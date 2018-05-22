#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class Buffer {
	public:
		Buffer(VkDevice& device, VkPhysicalDevice& physicalDevice);
		~Buffer();

		VkBuffer& get();

	private:
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	protected:
		void create(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

		void create(VkDeviceSize size, VkBufferUsageFlags usage,
			VkMemoryPropertyFlags properties);
		VkBuffer m_buffer;
		VkDeviceMemory m_bufferMemory;

		VkDevice& m_device;
		VkPhysicalDevice& m_physicalDevice;
	};
}
