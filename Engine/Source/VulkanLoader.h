#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Window.h>
#include <DebugCallback.h>
#include <Instance.h>
#include <PhysicalDevice.h>
#include <Utils/Log.h>
#include <Swapchain.h>
#include <QueueFamily.h>
#include <LogicalDevice.h>
#include <ImageViews.h>
#include <PipelineLayout.h>
#include <GraphicsPipeline.h>
#include <RenderPass.h>
#include <Framebuffers.h>
#include <CommandPool.h>
#include <CommandBuffers.h>
#include <SyncObject.h>

#include <memory>
#include <vector>
#include <set>
#include <algorithm>

namespace Ly {
	class VulkanLoader
	{
	public:
		VulkanLoader(std::unique_ptr<Window>& window);
		~VulkanLoader();

		void drawFrame();
		void waitIdle();

	private:
		void initVulkan();
		void createValidationLayers();
		void createInstance();
		void setupDebugCallback();
		void createSurface();
		void createPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void createImageViews();
		void createRenderPass();
		void createPipelineLayout();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();
		void recreateSwapchain();
		void cleanupSwapChain();

		const std::vector<const char*> m_deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		const int MAX_FRAMES_IN_FLIGHT = 2;
		size_t currentFrame = 0;

		std::unique_ptr<Ly::Window>& m_window;
		std::unique_ptr<Ly::Instance> m_instance;
		std::unique_ptr<Ly::ValidationLayers> m_validationLayers;
		std::string m_appName = "Triangle";
		std::string m_engineName = "LycanthEngine";
		std::unique_ptr<Ly::DebugCallback> m_callback;
		VkSurfaceKHR m_surface;
		std::unique_ptr<Ly::PhysicalDevice> m_physicalDevice;
		std::unique_ptr<Ly::LogicalDevice> m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		std::unique_ptr<Ly::Swapchain> m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;
		std::unique_ptr<Ly::ImageViews> m_swapChainImageViews;
		std::unique_ptr<Ly::PipelineLayout> m_pipelineLayout;
		std::unique_ptr<Ly::GraphicsPipeline> m_graphicsPipeline;
		std::unique_ptr<Ly::RenderPass> m_renderPass;
		std::unique_ptr<Ly::Framebuffers> m_swapChainFramebuffers;
		std::unique_ptr<Ly::CommandPool> m_commandPool;
		std::unique_ptr<Ly::CommandBuffers> m_commandBuffers;
		std::vector<std::unique_ptr<Ly::SyncObject>> m_syncObjects;
	};
}
