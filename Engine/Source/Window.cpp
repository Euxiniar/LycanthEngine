#include <Window.h>

namespace Ly 
{
	Window::Window(std::string title, int width, int height)
		: m_title(title), m_width(width), m_height(height)
	{
		run();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Window::poolEvents()
	{
		glfwPollEvents();
	}

	void Window::run()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	}
}
