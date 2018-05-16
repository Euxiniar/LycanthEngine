#include <Instance.h>

namespace Ly {


	Instance::Instance(const char * appName, const char * engineName, std::vector<const char*> validationLayers)
	{
		createInstance(appName, engineName, validationLayers);
	}

	Instance::~Instance()
	{
		vkDestroyInstance(m_instance, nullptr);
	}

	VkInstance & Instance::get()
	{
		return m_instance;
	}

	void Instance::createInstance(const char * appName, const char * engineName, std::vector<const char*>& validationLayers)
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = appName;
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = engineName;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_1;

		Ly::Extensions::showAvailableInstanceExtensions();

		//Get the required Vulkan extensions
		auto extensions = Ly::Extensions::getRequiredInstanceExtensions();

		//Specify instance informations
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		//Enable Validation Layers
		if (Ly::ValidationLayers::areEnabled()) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		//Create instance
		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
			Ly::Log::error("Failed to create the Vulkan instance !");
		}
	}
}
