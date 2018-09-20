#include "Application.hpp"
#include "MainFrame.hpp"

namespace vkapp
{
	Application::Application()
		: App(appName)
	{
	}
	std::unique_ptr<common::MainFrame> Application::doCreateMainFrame()
	{
		return std::make_unique<MainFrame>();
	}
}