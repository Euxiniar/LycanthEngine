#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class DescriptorPool {
	public:
		DescriptorPool(VkDevice& device, 
			uint32_t descriptorCount, 
			uint32_t maxSets);
		~DescriptorPool();
		VkDescriptorPool& get();

	private :
		VkDevice& m_device;
		VkDescriptorPool m_descriptorPool;
		uint32_t m_descriptorCount;
		uint32_t m_maxSets;

		void create();
	};
}