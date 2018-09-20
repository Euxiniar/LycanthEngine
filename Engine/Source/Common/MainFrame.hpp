#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include "Prerequisites.hpp"


namespace common
{
	class MainFrame {
	public:
		MainFrame(std::string const & name);
		~MainFrame();
		void initialise();
		void cleanup();

		bool framebufferResized = false;

	private:
		void timer();
		void close();

	private:
		std::string m_name;
		GLFWwindow *m_window;
		Ly::RendererPtr m_renderer;
	};
}