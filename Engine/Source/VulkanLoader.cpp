#include <VulkanLoader.h>

namespace Ly 
{
	VulkanLoader::VulkanLoader()
	{
		initVulkan();
	}

	VulkanLoader::~VulkanLoader()
	{
		if (enableValidationLayers) {
			m_callback.reset();
		}
		vkDestroyInstance(m_instance, nullptr);
	}

	void VulkanLoader::initVulkan()
	{
		createInstance();
		setupDebugCallback();
	}

	void VulkanLoader::createInstance()
	{
		if (enableValidationLayers && !checkValidationLayerSupport()) {
			Ly::Log::error("validation layers requested, but not available!");
		}

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = m_appName.c_str();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = m_engineName.c_str();
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_1;

		//Shows all avalaibale extensions
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> AvalaibleExtensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, AvalaibleExtensions.data());

		Ly::Log::info("available extensions:");
		for (const auto& extension : AvalaibleExtensions) {
			Ly::Log::info(extension.extensionName);
		}

		//Get the required Vulkan extensions
		auto extensions = getRequiredExtensions();

		//Specify instance informations
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();
		
		//Enable Validation Layers
		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
			createInfo.ppEnabledLayerNames = m_validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		//Create instance
		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
			Ly::Log::error("Failed to create the Vulkan instance !");
		}
	}

	bool VulkanLoader::checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	std::vector<const char*> VulkanLoader::getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	void VulkanLoader::setupDebugCallback()
	{
		if (!enableValidationLayers) {
			return;
		}
		else {
			m_callback = std::make_unique<DebugCallback>(m_instance);
		}
	}
}