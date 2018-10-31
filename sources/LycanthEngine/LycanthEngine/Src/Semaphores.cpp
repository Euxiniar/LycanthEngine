#include "Semaphores.hpp"

namespace Ly
{

	std::unique_ptr<Ly::Semaphores> Semaphores::create(Ly::Renderer& renderer, Ly::Swapchain& swapchain)
	{
		return std::unique_ptr < Ly::Semaphores>(new Ly::Semaphores(renderer, swapchain));
	}

	Semaphores::Semaphores(Ly::Renderer & renderer, Ly::Swapchain& swapchain)
	{
		for (uint32_t n_semaphore = 0;
			n_semaphore < swapchain.get_n_swapchain_images();
			++n_semaphore)
		{
			Anvil::SemaphoreUniquePtr new_signal_semaphore_ptr;
			Anvil::SemaphoreUniquePtr new_wait_semaphore_ptr;

			{
				auto create_info_ptr = Anvil::SemaphoreCreateInfo::create(renderer.get_device()->get());

				new_signal_semaphore_ptr = Anvil::Semaphore::create(std::move(create_info_ptr));
			}

			{
				auto create_info_ptr = Anvil::SemaphoreCreateInfo::create(renderer.get_device()->get());

				new_wait_semaphore_ptr = Anvil::Semaphore::create(std::move(create_info_ptr));
			}

			new_signal_semaphore_ptr->set_name_formatted("Signal semaphore [%d]",
				n_semaphore);
			new_wait_semaphore_ptr->set_name_formatted("Wait semaphore [%d]",
				n_semaphore);

			m_frame_signal_semaphores.push_back(std::move(new_signal_semaphore_ptr));
			m_frame_wait_semaphores.push_back(std::move(new_wait_semaphore_ptr));
		}
	}

}