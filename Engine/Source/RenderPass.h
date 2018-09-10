#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>
#include <array>

namespace Ly {
	class RenderPass {
	public:
		RenderPass(VkDevice & device,
		VkFormat& swapChainImageFormat, VkFormat depthFormat);
		~RenderPass();
		VkRenderPass& get();

	private:
		void create();
		VkDevice & m_device;
		VkFormat& m_swapChainImageFormat;
		VkFormat m_depthFormat;

		VkRenderPass m_renderPass;
	};
}
