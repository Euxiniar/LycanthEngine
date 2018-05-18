#include <Renderer.h>

namespace Ly
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

	void Renderer::initWindow()
	{
		try {
			m_window = std::make_unique<Ly::Window>();
		}
		catch (const std::runtime_error&) {
			Ly::Log::error("Error during the window creation process");
		}
	}

	void Renderer::initVulkan()
	{
		try {
			m_vulkanLoader = std::make_unique<Ly::VulkanLoader>(m_window);
		}
		catch (const std::runtime_error&) {
			Ly::Log::error("Error during the vulkanLoader creation process");
		}
	}

	void Renderer::mainLoop()
	{
		while (!m_window->shouldClose()) {
			m_window->poolEvents();
			m_vulkanLoader->drawFrame();
		}
		m_vulkanLoader->waitIdle();
	}

	void Renderer::cleanup()
	{
	}
}
