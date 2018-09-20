#include "Application.hpp"

namespace common
{

	App::App(const std::string &name)
		: m_name{ name }
	{
	}

	void App::init()
	{
		m_mainFrame = doCreateMainFrame();
		m_mainFrame->initialise();
	}

	void App::exit()
	{
	}

	void App::updateFps(std::chrono::microseconds const & durationGpu, 
		std::chrono::microseconds const & durationCpu)
	{
	}

	void App::updateFps(std::chrono::microseconds & duration)
	{
	}
}
