#pragma once
#include <wrappers/semaphore.h>
#include <misc/semaphore_create_info.h>
#include "Renderer.hpp"
#include "Swapchain.hpp"
#include <vector>

namespace Ly
{
	class Semaphores
	{
	public:
		static std::unique_ptr<Ly::Semaphores> create(Ly::Renderer& renderer, Ly::Swapchain& swapchain);
		Semaphores(Ly::Renderer& renderer, Ly::Swapchain& swapchain);
	private:
		std::vector<Anvil::SemaphoreUniquePtr> m_frame_signal_semaphores;
		std::vector<Anvil::SemaphoreUniquePtr> m_frame_wait_semaphores;
	};
}