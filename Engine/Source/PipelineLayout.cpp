#include <PipelineLayout.h>

namespace Ly {
	PipelineLayout::PipelineLayout(VkDevice& device, VkDescriptorSetLayout& descriptorSetLayout)
		: m_device(device), m_descriptorSetLayout(descriptorSetLayout)
	{
		create();
	}

	PipelineLayout::~PipelineLayout()
	{
		vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
	}

	void PipelineLayout::create() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 1;
		pipelineLayoutInfo.pSetLayouts = &m_descriptorSetLayout;
		//pipelineLayoutInfo.pushConstantRangeCount = 0;

		if (vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
			Ly::Log::error("Failed to create pipeline layout!");
		}
	}
	VkPipelineLayout & PipelineLayout::get()
	{
		return m_pipelineLayout;
	}
}
