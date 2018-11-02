#pragma once
#include <wrappers/framebuffer.h>
#include "Renderer.hpp"
#include "Prerequisites.hpp"
#include "Swapchain.hpp"
#include <array>
#include <misc/framebuffer_create_info.h>

namespace Ly
{
	class Framebuffers
	{
	public:
		static std::unique_ptr<Ly::Framebuffers> create(Ly::Renderer& renderer, Ly::Swapchain& swapchain);
		Framebuffers(Ly::Renderer& renderer, Ly::Swapchain& swapchain);
		~Framebuffers();
		std::array<Anvil::FramebufferUniquePtr, N_SWAPCHAIN_IMAGES>& get_fbos();
	private:
		std::array<Anvil::FramebufferUniquePtr, N_SWAPCHAIN_IMAGES> m_fbos;
	};
}