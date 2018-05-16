#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>
#include <QueueFamily.h>
#include <set>
#include <ValidationLayers.h>

namespace Ly {
	class LogicalDevice {
	public:
		LogicalDevice(VkPhysicalDevice physicalDevice, 
			VkSurfaceKHR surface, 
			const std::vector<const char*>& validationLayers, 
			const std::vector<const char*>& deviceExtensions,
			VkQueue& graphicsQueue, 
			VkQueue& presentQueue);
		~LogicalDevice();
		VkDevice& get();
		
	private:
		VkDevice m_device;
		VkPhysicalDevice& m_physicalDevice;
		VkSurfaceKHR& m_surface;
		const std::vector<const char*>& m_validationLayers;
		const std::vector<const char*>& m_deviceExtensions;
		VkQueue& m_graphicsQueue;
		VkQueue& m_presentQueue;
		void create();
	};
}
