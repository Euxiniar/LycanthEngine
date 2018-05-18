#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class Semaphores {
	public:
		Semaphores(VkDevice& device);
		~Semaphores();
		VkSemaphore& getImageAvailableSemaphore();
		VkSemaphore& getRenderFinishedSemaphore();
		
	private:
		VkDevice & m_device;
		void create();

		VkSemaphore m_imageAvailableSemaphore;
		VkSemaphore m_renderFinishedSemaphore;
	};
}
