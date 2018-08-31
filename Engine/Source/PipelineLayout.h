#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class PipelineLayout {
	public:
		PipelineLayout(VkDevice& device, VkDescriptorSetLayout& descriptorSetLayout);
		~PipelineLayout();

		void create();
		VkPipelineLayout& get();

	private:
		VkDevice & m_device;
		VkDescriptorSetLayout& m_descriptorSetLayout;

		VkPipelineLayout m_pipelineLayout;
	};
}
