#include <VulkanLoader.h>

namespace Ly 
{
	VulkanLoader::VulkanLoader(std::unique_ptr<Window>& window)
		: m_window(window)
	{
		initVulkan();
	}

	VulkanLoader::~VulkanLoader()
	{
		m_commandPool.reset();
		m_swapChainFramebuffers.reset();
		m_graphicsPipeline.reset();
		m_pipelineLayout.reset();
		m_renderPass.reset();
		m_swapChainImageViews.reset();
		m_swapChain.reset();
		m_device.reset();
		if (Ly::ValidationLayers::areEnabled()) {
			m_callback.reset();
		}
		vkDestroySurfaceKHR(m_instance->get(), m_surface, nullptr);
		m_instance.reset();
	}

	void VulkanLoader::initVulkan()
	{
		createValidationLayers();
		createInstance();
		setupDebugCallback();
		createSurface();
		createPhysicalDevice();
		createLogicalDevice();
		createSwapChain();
		createImageViews();
		createRenderPass();
		createPipelineLayout();
		createGraphicsPipeline();
	}

	void VulkanLoader::createValidationLayers()
	{
		m_validationLayers = std::make_unique<Ly::ValidationLayers>("VK_LAYER_LUNARG_standard_validation");
	}

	void VulkanLoader::createInstance()
	{
		m_instance = std::make_unique<Ly::Instance>(m_appName.c_str(), m_engineName.c_str(), m_validationLayers->get());
	}

	void VulkanLoader::setupDebugCallback()
	{
		if (!Ly::ValidationLayers::areEnabled()) {
			return;
		}
		else {
			m_callback = std::make_unique<DebugCallback>(m_instance->get());
		}
	}

	void VulkanLoader::createSurface()
	{
		if (glfwCreateWindowSurface(m_instance->get(), m_window->m_window, nullptr, &m_surface) != VK_SUCCESS) {
			Ly::Log::error("Failed to create Window Surface !");
		}
	}

	void VulkanLoader::createPhysicalDevice()
	{
		m_physicalDevice = std::make_unique<Ly::PhysicalDevice>(m_instance->get(), m_surface);
	}

	void VulkanLoader::createLogicalDevice()
	{
		m_device = std::make_unique<Ly::LogicalDevice>(m_physicalDevice->get(), 
			m_surface, m_validationLayers->get(), 
			m_deviceExtensions, m_graphicsQueue, m_presentQueue);
	}

	void VulkanLoader::createSwapChain()
	{
		m_swapChain = std::make_unique<Swapchain>(m_window, m_physicalDevice->get(), 
			m_surface, m_device->get(), m_swapChainImages, m_swapChainImageFormat, 
			m_swapChainExtent);
	}

	void VulkanLoader::createImageViews()
	{
		m_swapChainImageViews = std::make_unique<Ly::ImageViews>(m_device->get(), m_swapChainImages, m_swapChainImageFormat);
	}

	void VulkanLoader::createRenderPass()
	{
		m_renderPass = std::make_unique<Ly::RenderPass>(m_device->get(), m_swapChainImageFormat);
	}

	void VulkanLoader::createPipelineLayout()
	{
		m_pipelineLayout = std::make_unique<Ly::PipelineLayout>(m_device->get());
	}

	void VulkanLoader::createGraphicsPipeline()
	{
		m_graphicsPipeline = std::make_unique<Ly::GraphicsPipeline>(m_device->get(), m_swapChainExtent, 
			m_pipelineLayout->get(), m_renderPass->get());
	}

	void VulkanLoader::createFramebuffers()
	{
		m_swapChainFramebuffers = std::make_unique<Ly::Framebuffers>(m_device->get(), 
			m_swapChainImageViews->get(), m_renderPass->get(), m_swapChainExtent);
	}

	void VulkanLoader::createCommandPool()
	{
		m_commandPool = std::make_unique<Ly::CommandPool>(m_device->get(), m_physicalDevice->get(), m_surface);
	}

	void VulkanLoader::createCommandBuffers()
	{
		m_commandBuffers = std::make_unique<Ly::CommandBuffers>(m_device->get(), m_commandPool->get(), 
			m_swapChainFramebuffers->get(), m_graphicsPipeline->get(), m_renderPass->get(), m_swapChainExtent);
	}
}
