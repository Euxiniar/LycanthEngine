#pragma once
#include <Utils/Log.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <QueueFamily.h>
#include <Extensions.h>
#include <Swapchain.h>

namespace Ly {
	class PhysicalDevice {
	public:
		PhysicalDevice(VkInstance & instance, VkSurfaceKHR& surface);
		VkPhysicalDevice& get();

	private:
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
		VkInstance& m_instance;
		VkSurfaceKHR& m_surface;
		const std::vector<const char*> m_deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	};
}