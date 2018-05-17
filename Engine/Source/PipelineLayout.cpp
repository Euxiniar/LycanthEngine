#include <PipelineLayout.h>

namespace Ly {
	PipelineLayout::PipelineLayout(VkDevice& device)
		: m_device(device)
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
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pushConstantRangeCount = 0;

		if (vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
			Ly::Log::error("Failed to create pipeline layout!");
		}
	}
	VkPipelineLayout & PipelineLayout::get()
	{
		return m_pipelineLayout;
	}
}
