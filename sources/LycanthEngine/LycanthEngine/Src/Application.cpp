#include "Application.hpp"

namespace Ly
{
	
	Application::Application()
	{

	}

	Application::Application(std::string appName)
		: m_appName(appName)
	{
	}

	Application::~Application()
	{
		deinit();
	}

	void Application::init()
	{
		m_renderer_ptr = Renderer::create(m_appName, ENGINE_NAME, true);
		m_window_ptr = Window::create(m_appName, 1280, 720, std::bind(&Application::draw_frame,
			this));
		m_swapchain_ptr = Swapchain::create(*m_renderer_ptr, *m_window_ptr);
		m_buffers_ptr = Buffers::create(*m_renderer_ptr);
		m_dsg_ptr = Descriptor_Set_Group::create(*m_renderer_ptr, *m_buffers_ptr);
		m_framebuffers_ptr = Framebuffers::create(*m_renderer_ptr, *m_swapchain_ptr);
		m_semaphores_ptr = Semaphores::create(*m_renderer_ptr, *m_swapchain_ptr);
		m_shaders_ptr = Shaders::create(*m_renderer_ptr);
		m_gfx_ptr = Gfx_pipelines::create(*m_renderer_ptr, *m_swapchain_ptr, *m_dsg_ptr, *m_shaders_ptr);
		m_command_buffers_ptr = Command_buffers::create(*m_renderer_ptr, *m_swapchain_ptr, *m_buffers_ptr, *m_framebuffers_ptr, *m_gfx_ptr, *m_dsg_ptr);
	}

	void Application::deinit()
	{
		auto gfx_pipeline_manager_ptr = m_renderer_ptr->get_device()->get()->get_graphics_pipeline_manager();
		Anvil::Vulkan::vkDeviceWaitIdle(m_renderer_ptr->get_device()->get()->get_device_vk());
		if (m_gfx_ptr->get_pipeline_id() != UINT32_MAX)
		{
			gfx_pipeline_manager_ptr->delete_pipeline(m_gfx_ptr->get_pipeline_id());

			m_gfx_ptr->set_pipeline_id(UINT32_MAX);
		}

		m_semaphores_ptr.reset();

		m_swapchain_ptr.reset();

		for (uint32_t n_swapchain_image = 0;
			n_swapchain_image < N_SWAPCHAIN_IMAGES;
			++n_swapchain_image)
		{
			m_command_buffers_ptr->get_command_buffer(n_swapchain_image).reset();
		}
		m_framebuffers_ptr.reset();

		m_buffers_ptr->get_data_buffer_ptr().reset();
		m_dsg_ptr.reset();
		m_shaders_ptr->get_fragment_shader().reset();
		m_buffers_ptr->get_mesh_data_buffer_ptr().reset();
		m_gfx_ptr.reset();
		m_shaders_ptr->get_vertex_shader().reset();

		m_renderer_ptr.reset();

		m_window_ptr.reset();
	}

	void Application::run()
	{
		m_window_ptr->run();
	}

	void Application::draw_frame()
	{
		Anvil::Semaphore*               curr_frame_signal_semaphore_ptr = nullptr;
		Anvil::Semaphore*               curr_frame_wait_semaphore_ptr = nullptr;
		static uint32_t                 n_frames_rendered = 0;
		uint32_t                        n_swapchain_image;
		Anvil::Queue*                   present_queue_ptr = m_renderer_ptr->get_device()->get()->get_universal_queue(0);
		Anvil::Semaphore*               present_wait_semaphore_ptr = nullptr;
		const Anvil::PipelineStageFlags wait_stage_mask = Anvil::PipelineStageFlagBits::ALL_COMMANDS_BIT;

		/* Determine the signal + wait semaphores to use for drawing this frame */
		m_semaphores_ptr->set_n_last_semaphore_used((m_semaphores_ptr->get_n_last_semaphore_used() + 1) % m_swapchain_ptr->get_n_swapchain_images());

		curr_frame_signal_semaphore_ptr = m_semaphores_ptr->get_frame_signal_semaphore(m_semaphores_ptr->get_n_last_semaphore_used()).get();
		curr_frame_wait_semaphore_ptr = m_semaphores_ptr->get_frame_wait_semaphore(m_semaphores_ptr->get_n_last_semaphore_used()).get();

		present_wait_semaphore_ptr = curr_frame_signal_semaphore_ptr;

		/* Determine the semaphore which the swapchain image */
		n_swapchain_image = m_swapchain_ptr->get_swapchain()->acquire_image(curr_frame_wait_semaphore_ptr,
			true); /* in_should_block */

	/* Submit work chunk and present */
		m_buffers_ptr->update_data_ub_contents(*m_renderer_ptr, n_swapchain_image);

		present_queue_ptr->submit(
			Anvil::SubmitInfo::create(m_command_buffers_ptr->get_command_buffer(n_swapchain_image).get(),
				1, /* n_semaphores_to_signal */
				&curr_frame_signal_semaphore_ptr,
				1, /* n_semaphores_to_wait_on */
				&curr_frame_wait_semaphore_ptr,
				&wait_stage_mask,
				false /* should_block */)
		);

		present_queue_ptr->present(m_swapchain_ptr->get_swapchain().get(),
			n_swapchain_image,
			1, /* n_wait_semaphores */
			&present_wait_semaphore_ptr);

		++n_frames_rendered;
	}

}
