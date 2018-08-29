#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class CommandPool {
	public:
		CommandPool(VkDevice& device, int queueFamilyIndice);
		~CommandPool();

		VkCommandPool& get();

	private:
		VkCommandPool m_commandPool;
		int m_queueFamilyIndice;
		VkDevice& m_device;

		void create();
	};
}
