#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class SyncObject {
	public:
		SyncObject(VkDevice& device);
		~SyncObject();
		VkSemaphore& getImageAvailableSemaphore();
		VkSemaphore& getRenderFinishedSemaphore();
		VkFence& getInFlightFence();
		
	private:
		VkDevice & m_device;
		void create();

		VkSemaphore m_imageAvailableSemaphore;
		VkSemaphore m_renderFinishedSemaphore;

		VkFence inFlightFence;
	};
}
