#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <fstream>
#include <Utils/Log.h>
#include <ShaderModule.h>
#include <memory>

namespace Ly {
	class GraphicsPipeline {
	public:
		GraphicsPipeline(VkDevice& device, VkExtent2D& swapChainExtent);
		~GraphicsPipeline();

		void create();
		VkPipelineLayout& get();

	private:
		VkDevice & m_device;
		VkExtent2D& m_swapChainExtent;

		VkPipelineLayout m_pipelineLayout;

		std::vector<char> readFile(const std::string& filename);
	};
}
