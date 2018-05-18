#include <CommandPool.h>

namespace Ly {
	CommandPool::CommandPool(VkDevice& device, VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface)
		: m_device(device), m_physicalDevice(physicalDevice), m_surface(surface)
	{
		create();
	}

	CommandPool::~CommandPool()
	{
		vkDestroyCommandPool(m_device, m_commandPool, nullptr);
	}

	VkCommandPool & CommandPool::get()
	{
		return m_commandPool;
	}

	void CommandPool::create()
	{
		QueueFamilyIndices queueFamilyIndices = Ly::QueueFamily::findQueueFamilies(m_physicalDevice, m_surface);

		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
		poolInfo.flags = 0;

		if (vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS) {
			Ly::Log::error ("Failed to create command pool!");
		}

	}

}
