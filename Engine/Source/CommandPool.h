#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <QueueFamily.h>

namespace Ly {
	class CommandPool {
	public:
		CommandPool(VkDevice& device, VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface);
		~CommandPool();

		VkCommandPool& get();

	private:
		VkCommandPool m_commandPool;

		VkDevice& m_device;
		VkPhysicalDevice& m_physicalDevice;
		VkSurfaceKHR& m_surface;

		void create();
	};
}
