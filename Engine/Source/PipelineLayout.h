#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class PipelineLayout {
	public:
		PipelineLayout(VkDevice& device);
		~PipelineLayout();

		void create();
		VkPipelineLayout& get();

	private:
		VkDevice & m_device;

		VkPipelineLayout m_pipelineLayout;
	};
}
