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

	void Application::run()
	{
		m_window_ptr->run();
	}

	void Application::draw_frame()
	{
	}

}
