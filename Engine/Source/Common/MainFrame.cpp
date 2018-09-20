#include "MainFrame.hpp"

namespace common
{
	static void framebufferResizeCallback(GLFWwindow* window, int, int) {
		auto windowApp = reinterpret_cast<MainFrame*>(glfwGetWindowUserPointer(window));
		windowApp->framebufferResized = true;
	}

	MainFrame::MainFrame(std::string const & name)
		: m_name{ name }
	{

	}

	MainFrame::~MainFrame()
	{
		cleanup();
	}

	void MainFrame::initialise()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		m_window = glfwCreateWindow(width, height, m_name.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
	}

	void MainFrame::cleanup()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void MainFrame::timer()
	{

	}

	void MainFrame::close()
	{

	}
}