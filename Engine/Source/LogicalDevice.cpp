#include <LogicalDevice.h>

namespace Ly {
	LogicalDevice::LogicalDevice(VkPhysicalDevice physicalDevice,
		VkSurfaceKHR surface,
		const std::vector<const char*>& validationLayers,
		const std::vector<const char*>& deviceExtensions,
		VkQueue& graphicsQueue,
		VkQueue& presentQueue)
		: m_physicalDevice(physicalDevice), m_surface(surface), 
		m_validationLayers(validationLayers), m_deviceExtensions(deviceExtensions),
		m_graphicsQueue(graphicsQueue), m_presentQueue(presentQueue)
	{
		create();
	}

	LogicalDevice::~LogicalDevice()
	{
		vkDestroyDevice(m_device, nullptr);
	}

	VkDevice& LogicalDevice::get()
	{
		return m_device;
	}

	void LogicalDevice::create()
	{
		QueueFamilyIndices indices = Ly::QueueFamily::findQueueFamilies(m_physicalDevice, m_surface);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

		float queuePriority = 1.0f;
		for (int queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = m_deviceExtensions.data();

		if (Ly::ValidationLayers::areEnabled()) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
			createInfo.ppEnabledLayerNames = m_validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
			Ly::Log::error("Failed to create logical device !");
		}

		vkGetDeviceQueue(m_device, indices.graphicsFamily, 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, indices.presentFamily, 0, &m_presentQueue);
	}
}
