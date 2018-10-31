#pragma once
#include <memory>
#include <wrappers/swapchain.h>
#include <wrappers/rendering_surface.h>
#include <wrappers/queue.h>

#include "Renderer.hpp"
#include "Window.hpp"
#include "Prerequisites.hpp"

namespace Ly
{
	class Swapchain
	{
	public:
		static std::unique_ptr<Ly::Swapchain> create(Ly::Renderer& renderer, Ly::Window& window);
		Swapchain(Ly::Renderer& renderer, Ly::Window& window);
		~Swapchain();
		Anvil::SwapchainUniquePtr& get_swapchain();

	private:
		Anvil::SwapchainUniquePtr m_swapchain_ptr;
		Anvil::RenderingSurfaceUniquePtr m_rendering_surface_ptr;
		Anvil::Queue* m_present_queue_ptr;

		const uint32_t m_n_swapchain_images;
	};
}