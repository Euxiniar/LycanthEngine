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
		double lastTime = glfwGetTime();
		int nbFrames = 0;

		while (!m_window->shouldClose()) {
			double currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
				// printf and reset timer
				printf("%i Frames per second\n", (int)nbFrames);
				nbFrames = 0;
				lastTime += 1.0;
			}
			m_window->poolEvents();
			m_vulkanLoader->drawFrame();
		}
		m_vulkanLoader->waitIdle();
	}

	void Renderer::cleanup()
	{
	}
}
