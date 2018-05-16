#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>

namespace Ly {
	class RenderPass {
	public:
		RenderPass(VkDevice & device,
		VkFormat& swapChainImageFormat);
		~RenderPass();

	private:
		void create();
		VkDevice & m_device;
		VkFormat& m_swapChainImageFormat;

		VkRenderPass m_renderPass;
	};
}
