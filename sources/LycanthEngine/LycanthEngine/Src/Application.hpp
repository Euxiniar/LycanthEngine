#pragma once 
#include <memory>
#include "Renderer.hpp"
#include "Window.hpp"
#include "Swapchain.hpp"
#include "Buffers.hpp"
#include "Descriptor_Set_Group.hpp"
#include "Framebuffers.hpp"
#include "Semaphores.hpp"
#include "Shaders.hpp"

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
		std::unique_ptr<Buffers> m_buffers_ptr;
		std::unique_ptr<Descriptor_Set_Group> m_dsg_ptr;
		std::unique_ptr<Framebuffers> m_framebuffers_ptr;
		std::unique_ptr<Semaphores> m_semaphores_ptr;
		std::unique_ptr<Shaders> m_shaders_ptr;

		std::string m_appName = "Game";

		void draw_frame();
	};
}