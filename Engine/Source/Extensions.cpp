#include <Extensions.h>


namespace Ly {
	std::vector<const char*> Extensions::getRequiredInstanceExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (ValidationLayers::areEnabled()) {
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	void Extensions::showAvailableInstanceExtensions()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> AvalaibleExtensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, AvalaibleExtensions.data());

		Ly::Log::info("available extensions:");
		for (const auto& extension : AvalaibleExtensions) {
			Ly::Log::info(extension.extensionName);
		}
	}

	bool Extensions::checkDeviceExtensionSupport(VkPhysicalDevice & device, std::vector<const char *> deviceExtensions)
	{
		uint32_t extensionsCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionsCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}
}
