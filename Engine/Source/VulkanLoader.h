#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <DebugCallback.h>
#include <Utils/Log.h>

#include <memory>
#include <vector>

namespace Ly {
	class VulkanLoader
	{
	public:
		VulkanLoader();
		~VulkanLoader();
	private:
		void initVulkan();
		void createInstance();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		void setupDebugCallback();

		const std::vector<const char*> m_validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
		};
#ifdef NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif
		VkInstance m_instance;
		std::string m_appName = "Vulkan";
		std::string m_engineName = "LycanthEngine";
		std::unique_ptr<Ly::DebugCallback> m_callback;
	};
}