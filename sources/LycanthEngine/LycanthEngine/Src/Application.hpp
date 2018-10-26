#pragma once 
#include <memory>
#include "Renderer.hpp"
#include "Window.hpp"
#include "Swapchain.hpp"

namespace Ly
{
	class Application
	{
	public:
		Application();
		Application(std::string appName);
		~Application();
		void init();
		void run();

	private:
		std::unique_ptr<Renderer> m_renderer_ptr;
		std::unique_ptr<Window> m_window_ptr;
		std::unique_ptr<Swapchain> m_swapchain_ptr;
		std::string m_appName = "Game";

		void draw_frame();
	};
}