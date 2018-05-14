#include <ValidationLayers.h>

namespace Ly {

	ValidationLayers::ValidationLayers(const char * validationLayers = "VK_LAYER_LUNARG_standard_validation")
	{
		m_validationLayers.push_back(validationLayers);
		areSupported();
	}

	ValidationLayers::~ValidationLayers()
	{
	}

	void ValidationLayers::areSupported()
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
				Ly::Log::error("Validation layers requested, but not available!");
			}
		}
	}

	std::vector<const char*>& ValidationLayers::get()
	{
		return m_validationLayers;
	}

	bool ValidationLayers::areEnabled()
	{
#ifdef NDEBUG
		return false;
#else
		return true;
#endif
	}


}