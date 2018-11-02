#include "Command_buffers.hpp"

namespace Ly
{
	std::unique_ptr<Ly::Command_buffers> Command_buffers::create(Ly::Renderer & renderer, Ly::Swapchain & swapchain, Ly::Buffers & buffers, Ly::Framebuffers & framebuffers, Ly::Gfx_pipelines & gfx_pipelines, Ly::Descriptor_Set_Group & dsg)
	{
		return std::unique_ptr<Ly::Command_buffers>(new Command_buffers(renderer, swapchain, buffers, framebuffers, gfx_pipelines, dsg));
	}
	Command_buffers::Command_buffers(Ly::Renderer& renderer, Ly::Swapchain& swapchain,
		Ly::Buffers& buffers, Ly::Framebuffers& framebuffers, Ly::Gfx_pipelines& gfx_pipelines, Ly::Descriptor_Set_Group& dsg)
	{
		auto                          gfx_pipeline_manager_ptr(renderer.get_device()->get()->get_graphics_pipeline_manager());
		Anvil::ImageSubresourceRange  image_subresource_range;
		std::unique_ptr<float[]>      luminance_data_ptr;
		uint32_t                      luminance_data_size;
		Anvil::Queue*                 universal_queue_ptr(renderer.get_device()->get()->get_universal_queue(0));

		image_subresource_range.aspect_mask = Anvil::ImageAspectFlagBits::COLOR_BIT;
		image_subresource_range.base_array_layer = 0;
		image_subresource_range.base_mip_level = 0;
		image_subresource_range.layer_count = 1;
		image_subresource_range.level_count = 1;

		Mesh::get_luminance_data(&luminance_data_ptr,
			&luminance_data_size);

		for (uint32_t n_command_buffer = 0;
			n_command_buffer < N_SWAPCHAIN_IMAGES;
			++n_command_buffer)
		{
			Anvil::PrimaryCommandBufferUniquePtr cmd_buffer_ptr;

			cmd_buffer_ptr = renderer.get_device()->get()->get_command_pool_for_queue_family_index(renderer.get_device()->get()->get_universal_queue(0)->get_queue_family_index())->alloc_primary_level_command_buffer();

			/* Start recording commands */
			cmd_buffer_ptr->start_recording(false, /* one_time_submit          */
				true); /* simultaneous_use_allowed */

	/* Switch the swap-chain image to the color_attachment_optimal image layout */
			{
				Anvil::ImageBarrier image_barrier(Anvil::AccessFlagBits::NONE,                       /* source_access_mask       */
					Anvil::AccessFlagBits::COLOR_ATTACHMENT_WRITE_BIT, /* destination_access_mask  */
					Anvil::ImageLayout::UNDEFINED,                  /* old_image_layout */
					Anvil::ImageLayout::COLOR_ATTACHMENT_OPTIMAL,   /* new_image_layout */
					universal_queue_ptr->get_queue_family_index(),
					universal_queue_ptr->get_queue_family_index(),
					swapchain.get_swapchain()->get_image(n_command_buffer),
					image_subresource_range);

				cmd_buffer_ptr->record_pipeline_barrier(Anvil::PipelineStageFlagBits::TOP_OF_PIPE_BIT,            /* src_stage_mask                 */
					Anvil::PipelineStageFlagBits::COLOR_ATTACHMENT_OUTPUT_BIT,/* dst_stage_mask                 */
					Anvil::DependencyFlagBits::NONE,
					0,                                                        /* in_memory_barrier_count        */
					nullptr,                                                  /* in_memory_barrier_ptrs         */
					0,                                                        /* in_buffer_memory_barrier_count */
					nullptr,                                                  /* in_buffer_memory_barrier_ptrs  */
					1,                                                        /* in_image_memory_barrier_count  */
					&image_barrier);
			}

			/* Make sure CPU-written data is flushed before we start rendering */
			Anvil::BufferBarrier buffer_barrier(Anvil::AccessFlagBits::HOST_WRITE_BIT,                 /* in_source_access_mask      */
				Anvil::AccessFlagBits::UNIFORM_READ_BIT,               /* in_destination_access_mask */
				universal_queue_ptr->get_queue_family_index(),         /* in_src_queue_family_index  */
				universal_queue_ptr->get_queue_family_index(),         /* in_dst_queue_family_index  */
				buffers.get_data_buffer_ptr().get(),
				buffers.get_ub_data_size_per_swapchain_image() * n_command_buffer, /* in_offset                  */
				buffers.get_ub_data_size_per_swapchain_image());

			cmd_buffer_ptr->record_pipeline_barrier(Anvil::PipelineStageFlagBits::HOST_BIT,
				Anvil::PipelineStageFlagBits::VERTEX_SHADER_BIT,
				Anvil::DependencyFlagBits::NONE,
				0,               /* in_memory_barrier_count        */
				nullptr,         /* in_memory_barriers_ptr         */
				1,               /* in_buffer_memory_barrier_count */
				&buffer_barrier,
				0,               /* in_image_memory_barrier_count  */
				nullptr);        /* in_image_memory_barriers_ptr   */

	/* 2. Render the geometry. */
			VkClearValue       attachment_clear_value;
			VkRect2D           render_area;
			VkShaderStageFlags shaderStageFlags = 0;

			attachment_clear_value.color.float32[0] = 1.0f;
			attachment_clear_value.color.float32[1] = 0.5f;
			attachment_clear_value.color.float32[2] = 0.2f;
			attachment_clear_value.color.float32[3] = 1.0f;

			render_area.extent.width = 1280;
			render_area.extent.height = 720;
			render_area.offset.x = 0;
			render_area.offset.y = 0;

			cmd_buffer_ptr->record_begin_render_pass(1, /* in_n_clear_values */
				&attachment_clear_value,
				framebuffers.get_fbos()[n_command_buffer].get(),
				render_area,
				gfx_pipelines.get_renderPass().get(),
				Anvil::SubpassContents::INLINE);
			{
				const uint32_t     data_ub_offset = static_cast<uint32_t>(buffers.get_ub_data_size_per_swapchain_image() * n_command_buffer);
				auto               ds_ptr = dsg.get_dsg()->get_descriptor_set(0 /* n_set */);
				const VkDeviceSize mesh_data_buffer_offset = 0;
				auto               mesh_data_buffer_raw_ptr = buffers.get_mesh_data_buffer_ptr().get();
				auto               pipeline_layout_ptr = gfx_pipeline_manager_ptr->get_pipeline_layout(gfx_pipelines.get_pipeline_id());

				cmd_buffer_ptr->record_bind_pipeline(Anvil::PipelineBindPoint::GRAPHICS,
					gfx_pipelines.get_pipeline_id());

				cmd_buffer_ptr->record_push_constants(pipeline_layout_ptr,
					Anvil::ShaderStageFlagBits::FRAGMENT_BIT | Anvil::ShaderStageFlagBits::VERTEX_BIT,
					0, /* in_offset */
					luminance_data_size,
					luminance_data_ptr.get());

				cmd_buffer_ptr->record_bind_descriptor_sets(Anvil::PipelineBindPoint::GRAPHICS,
					pipeline_layout_ptr,
					0, /* firstSet */
					1, /* setCount */
					&ds_ptr,
					1,               /* dynamicOffsetCount */
					&data_ub_offset); /* pDynamicOffsets    */

				cmd_buffer_ptr->record_bind_vertex_buffers(0, /* startBinding */
					1, /* bindingCount */
					&mesh_data_buffer_raw_ptr,
					&mesh_data_buffer_offset);

				cmd_buffer_ptr->record_draw(3,            /* in_vertex_count   */
					N_TRIANGLES,  /* in_instance_count */
					0,            /* in_first_vertex   */
					0);           /* in_first_instance */
			}
			cmd_buffer_ptr->record_end_render_pass();

			/* Close the recording process */
			cmd_buffer_ptr->stop_recording();

			m_command_buffers[n_command_buffer] = std::move(cmd_buffer_ptr);
		}
	}

	Command_buffers::~Command_buffers()
	{
	}

	Anvil::PrimaryCommandBufferUniquePtr& Command_buffers::get_command_buffer(uint32_t position)
	{
		return m_command_buffers[position];
	}

}