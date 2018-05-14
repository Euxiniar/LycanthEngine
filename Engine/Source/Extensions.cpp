#include <Extensions.h>


namespace Ly {
	std::vector<const char*> Extensions::getRequiredExtensions()
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

	void Extensions::showAvailableExtensions()
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
}
