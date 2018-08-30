#include <Window.h>

namespace Ly 
{
	static void framebufferResizeCallback(GLFWwindow* window, int, int) {
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	}

	Window::Window(std::string title, int width, int height)
		: m_title(title), m_width(width), m_height(height)
	{
		create();
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

	void Window::updateWindowSize()
	{
		glfwGetFramebufferSize(m_window, &m_width, &m_height);
	}

	void Window::setTitle(const char * title)
	{
		glfwSetWindowTitle(m_window, title);
	}

	void Window::create()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
		
	}
}
