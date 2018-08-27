#include "SyncObject.h"

namespace Ly {
	SyncObject::SyncObject(VkDevice & device)
		: m_device(device)
	{
		create();
	}

	SyncObject::~SyncObject()
	{
		vkDestroyFence(m_device, inFlightFence, nullptr);
		vkDestroySemaphore(m_device, m_imageAvailableSemaphore, nullptr);
		vkDestroySemaphore(m_device, m_renderFinishedSemaphore, nullptr);
	}

	VkSemaphore & SyncObject::getImageAvailableSemaphore()
	{
		return m_imageAvailableSemaphore;
	}

	VkSemaphore & SyncObject::getRenderFinishedSemaphore()
	{
		return m_renderFinishedSemaphore;
	}

	VkFence & SyncObject::getInFlightFence()
	{
		return inFlightFence;
	}

	void SyncObject::create()
	{
		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		if (vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_imageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_renderFinishedSemaphore) != VK_SUCCESS ||
			vkCreateFence(m_device, &fenceInfo, nullptr, &inFlightFence)) {
			Ly::Log::error("Failed to create synchronization objects for a frame !");
		}
	}
}
