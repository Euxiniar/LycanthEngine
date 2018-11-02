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
		~Semaphores();
		uint32_t get_n_last_semaphore_used();
		void set_n_last_semaphore_used(uint32_t value);
		Anvil::SemaphoreUniquePtr& get_frame_signal_semaphore(uint32_t position);
		Anvil::SemaphoreUniquePtr& get_frame_wait_semaphore(uint32_t position);
	private:
		std::vector<Anvil::SemaphoreUniquePtr> m_frame_signal_semaphores;
		std::vector<Anvil::SemaphoreUniquePtr> m_frame_wait_semaphores;
		uint32_t m_n_last_semaphore_used;
	};
}