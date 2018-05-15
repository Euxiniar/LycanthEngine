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
		for (auto imageView : m_swapChainImageViews) {
			vkDestroyImageView(m_device->get(), imageView, nullptr);
		}
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
		m_swapChain = std::make_unique<Swapchain>(m_window, m_physicalDevice->get(), m_surface, m_device->get(), m_swapChainImages, m_swapChainImageFormat, m_swapChainExtent);
	}

	void VulkanLoader::createImageViews()
	{
		m_swapChainImageViews.resize(m_swapChainImages.size());

		for (size_t i = 0; i < m_swapChainImages.size(); i++) {
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_swapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_swapChainImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_device->get(), &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS) {
				Ly::Log::error("Failed to create Image View !");
			}
		}
	}
}