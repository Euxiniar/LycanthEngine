#pragma once
#include "Renderer.hpp"
#include "Prerequisites.hpp"
#include "Mesh.hpp"
#include <memory>
#include <misc/memory_allocator.h>
#include <misc/buffer_create_info.h>
#include <wrappers/buffer.h>
#include <misc/time.h>

namespace Ly
{
	class Buffers
	{
	public:
		static std::unique_ptr<Ly::Buffers> create(Ly::Renderer& renderer);
		Buffers(Ly::Renderer& renderer);
		~Buffers();
		VkDeviceSize& get_ub_data_size_per_swapchain_image();
		Anvil::BufferUniquePtr& get_data_buffer_ptr();
		Anvil::BufferUniquePtr& get_mesh_data_buffer_ptr();

		void update_data_ub_contents(Ly::Renderer& renderer, uint32_t& in_n_swapchain_image);

	private:
		Anvil::BufferUniquePtr m_data_buffer_ptr;
		Anvil::BufferUniquePtr m_mesh_data_buffer_ptr;
		VkDeviceSize m_ub_data_size_per_swapchain_image;

		Anvil::Time m_time;
	};
}