#include "DescriptorPool.h"

namespace Ly {
	DescriptorPool::DescriptorPool(VkDevice & device, uint32_t descriptorCount, uint32_t maxSets) :
		m_device(device),
		m_descriptorCount(descriptorCount),
		m_maxSets(maxSets)
	{
		create();
	}

	DescriptorPool::~DescriptorPool()
	{
		vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);
	}

	VkDescriptorPool& Ly::DescriptorPool::get()
	{
		return m_descriptorPool;
	}

	void DescriptorPool::create()
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = m_descriptorCount;

		VkDescriptorPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;

		poolInfo.maxSets = m_maxSets;

		if (vkCreateDescriptorPool(m_device, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
			Ly::Log::error("Failed to create descriptor pool!");
		}
	}
}