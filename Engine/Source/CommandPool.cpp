#include <CommandPool.h>

namespace Ly {
	CommandPool::CommandPool(VkDevice& device, int queueFamilyIndice)
		: m_device(device), m_queueFamilyIndice(queueFamilyIndice)
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
		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = m_queueFamilyIndice;
		poolInfo.flags = 0;

		if (vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS) {
			Ly::Log::error ("Failed to create command pool!");
		}
	}

}
