#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <ShaderModule.h>
#include <fstream>
#include <memory>
#include <vector>

namespace Ly {
	class GraphicsPipeline {
	public:
		GraphicsPipeline(VkDevice& device,
		VkExtent2D& swapChainExtent,
		VkPipelineLayout& pipelineLayout,
		VkRenderPass& renderPass);
		~GraphicsPipeline();

		VkPipeline& get();
		
	private:
		VkDevice& m_device;
		VkExtent2D& m_swapChainExtent;
		VkPipelineLayout& m_pipelineLayout;
		VkRenderPass& m_renderPass;

		VkPipeline m_graphicsPipeline;

		std::vector<char> readFile(const std::string & filename);
		void create();
	};
}
