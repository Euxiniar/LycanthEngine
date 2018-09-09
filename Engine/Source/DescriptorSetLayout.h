#pragma once
#include <vulkan/vulkan.h>
#include <UniformBufferObject.hpp>
#include <Utils/Log.h>
#include <array>

namespace Ly {
	class DescriptorSetLayout {
	public:
		DescriptorSetLayout(VkDevice& device);
		~DescriptorSetLayout();
		VkDescriptorSetLayout& get();

	private:
		void create();
		VkDevice& m_device;
		VkDescriptorSetLayout m_descriptorSetLayout;
	};
}