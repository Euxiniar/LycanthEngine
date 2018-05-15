#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>

namespace Ly {
	struct SwapChainSupportDetails {
		//Min/Max number of images in the swapchain
		//Min/Max images size in the swapchain
		VkSurfaceCapabilitiesKHR capabilities;
		//Pixel Format/Color Space
		std::vector<VkSurfaceFormatKHR> formats;
		//Image resolution in the swapchain
		std::vector<VkPresentModeKHR> presentModes;
	};

	class Swapchain {
	public:
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

	};
}