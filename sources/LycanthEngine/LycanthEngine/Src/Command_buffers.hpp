#pragma once
#include "Renderer.hpp"
#include "Mesh.hpp"
#include "Swapchain.hpp"
#include "Buffers.hpp"
#include "Framebuffers.hpp"
#include "Gfx_pipelines.hpp"
#include "Descriptor_Set_Group.hpp"
#include <wrappers/command_pool.h>
#include <wrappers/command_buffer.h>
#include <wrappers/queue.h>
#include <array>

namespace Ly
{
	class Command_buffers
	{
	public :
		static std::unique_ptr<Ly::Command_buffers> create(Ly::Renderer& renderer, Ly::Swapchain& swapchain,
			Ly::Buffers& buffers, Ly::Framebuffers& framebuffers, Ly::Gfx_pipelines& gfx_pipelines, Ly::Descriptor_Set_Group& dsg);

		Command_buffers(Ly::Renderer& renderer, Ly::Swapchain& swapchain,
			Ly::Buffers& buffers, Ly::Framebuffers& framebuffers, Ly::Gfx_pipelines& gfx_pipelines, Ly::Descriptor_Set_Group& dsg);
		~Command_buffers();

		Anvil::PrimaryCommandBufferUniquePtr& get_command_buffer(uint32_t position);
	private:
		std::array<Anvil::PrimaryCommandBufferUniquePtr, N_SWAPCHAIN_IMAGES> m_command_buffers;
	};
}