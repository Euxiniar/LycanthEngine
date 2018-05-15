#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>

namespace Ly {
	struct QueueFamilyIndices {
		//Queue Family which supports graphics
		int graphicsFamily = -1;
		//Queue Family which supports display presentation
		int presentFamily = -1;

		bool matches() {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	class QueueFamily {
	public:
	static	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& device, VkSurfaceKHR& surface);
	};
}