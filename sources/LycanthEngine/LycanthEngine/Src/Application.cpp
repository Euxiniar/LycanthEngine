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
	}

	void Application::run()
	{
		m_window_ptr->run();
	}

	void Application::draw_frame()
	{
	}

}
