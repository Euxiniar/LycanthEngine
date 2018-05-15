#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ValidationLayers.h>
#include <vector>

namespace Ly {
	class Extensions {
	public:
		static std::vector<const char*> getRequiredInstanceExtensions();
		static void showAvailableInstanceExtensions();
	};
}