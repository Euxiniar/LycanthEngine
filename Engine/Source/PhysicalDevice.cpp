#include <PhysicalDevice.h>

namespace Ly {
	PhysicalDevice::PhysicalDevice(VkInstance & instance, VkSurfaceKHR & surface)
		: m_instance(instance), m_surface(surface)
	{
		pickPhysicalDevice();
	}

	VkPhysicalDevice& PhysicalDevice::get()
	{
		return m_physicalDevice;
	}

	void PhysicalDevice::pickPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			Ly::Log::error("Failed to find GPUs with Vulkan support !");
		}
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

		for (const auto& device : devices) {
			if (isDeviceSuitable(device)) {
				m_physicalDevice = device;
				break;
			}
		}

		if (m_physicalDevice == VK_NULL_HANDLE) {
			Ly::Log::error("Failed to find a suitable GPU !");
		}
	}

	bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = Ly::QueueFamily::findQueueFamilies(device, m_surface);

		bool extensionSupported = Ly::Extensions::checkDeviceExtensionSupport(device, m_deviceExtensions);

		bool swapChainAdequate = false;
		if (extensionSupported) {
			SwapChainSupportDetails swapChainSupport = Ly::Swapchain::querySwapChainSupport(device, m_surface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.matches() && extensionSupported && swapChainAdequate;
	}
}
