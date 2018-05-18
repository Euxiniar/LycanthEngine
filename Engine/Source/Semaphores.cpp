#include "Semaphores.h"

namespace Ly {
	Semaphores::Semaphores(VkDevice & device)
		: m_device(device)
	{
		create();
	}

	Semaphores::~Semaphores()
	{
		vkDestroySemaphore(m_device, m_imageAvailableSemaphore, nullptr);
		vkDestroySemaphore(m_device, m_renderFinishedSemaphore, nullptr);
	}

	VkSemaphore & Semaphores::getImageAvailableSemaphore()
	{
		return m_imageAvailableSemaphore;
	}

	VkSemaphore & Semaphores::getRenderFinishedSemaphore()
	{
		return m_renderFinishedSemaphore;
	}

	void Semaphores::create()
	{
		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		if (vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_imageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_renderFinishedSemaphore) != VK_SUCCESS) {

			Ly::Log::error("Failed to create semaphores!");
		}
	}
}
