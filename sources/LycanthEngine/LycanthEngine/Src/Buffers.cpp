#include "Buffers.hpp"

namespace Ly
{
	std::unique_ptr<Ly::Buffers> Buffers::create(Ly::Renderer & renderer)
	{
		return std::unique_ptr<Ly::Buffers>(new Buffers(renderer));
	}

	Buffers::Buffers(Ly::Renderer& renderer)
	{
		const unsigned char* mesh_data = Mesh().get_mesh_data();
		const uint32_t       mesh_data_size = Mesh().get_mesh_data_size();
		const VkDeviceSize   ub_data_size_per_swapchain_image = sizeof(int) * 4 + /* frame index + padding             */
			sizeof(float) * N_TRIANGLES * 4 + /* position (vec2) + rotation (vec2) */
			sizeof(float) * N_TRIANGLES +     /* luminance                         */
			sizeof(float) * N_TRIANGLES;      /* size                              */
		const auto           ub_data_alignment_requirement = renderer.get_device()->get()->get_physical_device_properties().core_vk1_0_properties_ptr->limits.min_uniform_buffer_offset_alignment;
		const auto           ub_data_size_total = N_SWAPCHAIN_IMAGES * (Anvil::Utils::round_up(ub_data_size_per_swapchain_image,
			ub_data_alignment_requirement));

		m_ub_data_size_per_swapchain_image = ub_data_size_total / N_SWAPCHAIN_IMAGES;

		/* Use a memory allocator to re-use memory blocks wherever possible */
		auto allocator_ptr = Anvil::MemoryAllocator::create_oneshot(renderer.get_device()->get());

		/* Set up a buffer to hold uniform data */
		{
			auto create_info_ptr = Anvil::BufferCreateInfo::create_no_alloc(renderer.get_device()->get(),
				ub_data_size_total,
				Anvil::QueueFamilyFlagBits::COMPUTE_BIT | Anvil::QueueFamilyFlagBits::GRAPHICS_BIT,
				Anvil::SharingMode::EXCLUSIVE,
				Anvil::BufferCreateFlagBits::NONE,
				Anvil::BufferUsageFlagBits::UNIFORM_BUFFER_BIT);

			m_data_buffer_ptr = Anvil::Buffer::create(std::move(create_info_ptr));
		}

		m_data_buffer_ptr->set_name("Data buffer");

		allocator_ptr->add_buffer(m_data_buffer_ptr.get(),
			Anvil::MemoryFeatureFlagBits::NONE); /* in_required_memory_features */

	/* Set up a buffer to hold mesh data */
		{
			auto create_info_ptr = Anvil::BufferCreateInfo::create_no_alloc(renderer.get_device()->get(),
				Mesh().get_mesh_data_size(),
				Anvil::QueueFamilyFlagBits::GRAPHICS_BIT,
				Anvil::SharingMode::EXCLUSIVE,
				Anvil::BufferCreateFlagBits::NONE,
				Anvil::BufferUsageFlagBits::VERTEX_BUFFER_BIT);

			m_mesh_data_buffer_ptr = Anvil::Buffer::create(std::move(create_info_ptr));
		}

		m_mesh_data_buffer_ptr->set_name("Mesh vertex data buffer");

		allocator_ptr->add_buffer(m_mesh_data_buffer_ptr.get(),
			Anvil::MemoryFeatureFlagBits::NONE); /* in_required_memory_features */

	/* Allocate memory blocks and copy data where applicable */
		m_mesh_data_buffer_ptr->write(0, /* start_offset */
			mesh_data_size,
			mesh_data);
	}

	Buffers::~Buffers()
	{
	}

	VkDeviceSize& Buffers::get_ub_data_size_per_swapchain_image()
	{
		return m_ub_data_size_per_swapchain_image;
	}

	Anvil::BufferUniquePtr& Buffers::get_data_buffer_ptr()
	{
		return m_data_buffer_ptr;
	}

	Anvil::BufferUniquePtr& Buffers::get_mesh_data_buffer_ptr()
	{
		return m_mesh_data_buffer_ptr;
	}

}