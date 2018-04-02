#pragma once
#include <Window.h>
#include <VulkanLoader.h>
#include <Utils/Log.h>
#include <memory>

namespace Ly {
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void run();
	private:
		void initWindow();
		void initVulkan();
		void mainLoop();
		void cleanup();

		std::unique_ptr<Ly::Window> m_window;
		std::unique_ptr<Ly::VulkanLoader> m_vulkanLoader;
	};
}