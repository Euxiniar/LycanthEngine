#include "Window.hpp"

namespace Ly
{
	std::unique_ptr<Ly::Window> Window::create(std::string appName, const int sizeX, const int sizeY, std::function<void()> loopFunction)
	{
		return std::unique_ptr<Ly::Window>(new Ly::Window(appName, sizeX, sizeY, loopFunction));
	}

	Window::Window(std::string appName, const int sizeX, const int sizeY, std::function<void()> loopFunction)
	{
#ifdef ENABLE_OFFSCREEN_RENDERING
		const Anvil::WindowPlatform platform = Anvil::WINDOW_PLATFORM_DUMMY_WITH_PNG_SNAPSHOTS;
#else
#ifdef _WIN32
		const Anvil::WindowPlatform platform = Anvil::WINDOW_PLATFORM_SYSTEM;
#else
		const Anvil::WindowPlatform platform = Anvil::WINDOW_PLATFORM_XCB;
#endif
#endif

		/* Create a window */
		m_window_ptr = Anvil::WindowFactory::create_window(platform,
			appName,
			sizeX,
			sizeY,
			true, /* in_closable */
			loopFunction
		);
	}

	Window::~Window()
	{

	}

	void Window::run()
	{
		m_window_ptr->run();
	}
}