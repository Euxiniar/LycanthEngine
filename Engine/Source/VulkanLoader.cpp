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
		vkDestroySwapchainKHR(m_device->get(), m_swapChain, nullptr);
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

	VkSurfaceFormatKHR VulkanLoader::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
			return{ VK_FORMAT_R8G8B8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
		}

		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_R8G8B8A8_UNORM && availableFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}
		return availableFormats[0];
	}

	VkPresentModeKHR VulkanLoader::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		VkPresentModeKHR bestMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

		for (const auto& availablePresentMode : availablePresentModes) {
if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
	return availablePresentMode;
}
else if (availablePresentMode == VK_PRESENT_MODE_FIFO_KHR) {
	bestMode = availablePresentMode;
}
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanLoader::chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;

		}
		else {
			VkExtent2D actualExtent = { (uint32_t)m_window->m_width, (uint32_t)m_window->m_height };

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	void VulkanLoader::createSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = Ly::Swapchain::querySwapChainSupport(m_physicalDevice->get(), m_surface);

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = Ly::QueueFamily::findQueueFamilies(m_physicalDevice->get(), m_surface);
		uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		//Not any transformation in the swapchain
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_device->get(), &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) {
			Ly::Log::error("Failed to create Swap Chain !");
		}

		vkGetSwapchainImagesKHR(m_device->get(), m_swapChain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_device->get(), m_swapChain, &imageCount, m_swapChainImages.data());

		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;
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