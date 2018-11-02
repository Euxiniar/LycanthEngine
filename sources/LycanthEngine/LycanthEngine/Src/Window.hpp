#pragma once
#include <misc/window_factory.h>
#include <string>
#include <memory>

namespace Ly
{
	class Window
	{
	public:
		static std::unique_ptr<Ly::Window> create(std::string appName, const int sizeX, const int sizeY, std::function<void()> loopFunction);

		Window(std::string appName, const int sizeX, const int sizeY, std::function<void()> loopFunction);
		~Window();
		void run();
		Anvil::WindowUniquePtr* get_window();

	private:
		Anvil::WindowUniquePtr m_window_ptr;
	};
}