#pragma once
#include <vulkan\vulkan.h>
#include <Utils\Log.h>

namespace Ly {
	class Buffer {
	public :
		Buffer(VkDevice &device,
			VkPhysicalDevice &physicalDevice,
			VkDeviceSize size,
			VkBufferUsageFlags usage,
			VkMemoryPropertyFlags properties);
		~Buffer();
		VkBuffer& get();
		VkDeviceMemory& getMemory();
		VkDeviceSize getSize();
		static uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

	protected:
		VkBuffer m_buffer;
		VkDeviceMemory m_bufferMemory;
		VkDevice& m_device;
		VkPhysicalDevice& m_physicalDevice;
		VkDeviceSize m_bufferSize;

	private:
		void create(VkBufferCreateInfo& bufferInfo, const VkMemoryPropertyFlags& properties);
	};
}