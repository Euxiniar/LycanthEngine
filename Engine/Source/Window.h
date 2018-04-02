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
		bool ShouldClose();
		void PoolEvents();
	private:
		void run();
		
		GLFWwindow* m_window;
		int m_width = 800;
		int m_height = 600;
		std::string m_title = "Vulkan";
	};
}