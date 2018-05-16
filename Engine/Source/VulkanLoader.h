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
#include <GraphicsPipeline.h>

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
		void createGraphicsPipeline();

		const std::vector<const char*> m_deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		std::unique_ptr<Ly::Window>& m_window;
		std::unique_ptr<Ly::Instance> m_instance;
		std::unique_ptr<Ly::ValidationLayers> m_validationLayers;
		std::string m_appName = "Vulkan";
		std::string m_engineName = "LycanthEngine";
		std::unique_ptr<Ly::DebugCallback> m_callback;
		VkSurfaceKHR m_surface;
		std::unique_ptr<Ly::PhysicalDevice> m_physicalDevice;
		std::unique_ptr<Ly::LogicalDevice> m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		std::unique_ptr<Swapchain> m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;
		std::unique_ptr<ImageViews> m_swapChainImageViews;
		std::unique_ptr<Ly::GraphicsPipeline> m_graphicsPipeline;
	};
}
