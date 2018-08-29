#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace Ly {
	class Window 
	{
	public:
		Window(std::string title = "Vulkan", int width = 800, int height = 600);
		~Window();
		bool shouldClose();
		void poolEvents();
		void updateWindowSize();

		GLFWwindow* m_window;
		int m_width = 800;
		int m_height = 600;
		std::string m_title = "Vulkan";
		bool framebufferResized = false;

	private:
		void create();
	};
}
