#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ValidationLayers.h>
#include <vector>
#include <set>

namespace Ly {
	class Extensions {
	public:
		static std::vector<const char*> getRequiredInstanceExtensions();
		static void showAvailableInstanceExtensions();
		static bool checkDeviceExtensionSupport(VkPhysicalDevice & device, std::vector<const char*> deviceExtensions);
	};
}
