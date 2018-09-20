#pragma once
#include <string>
#include <chrono>
#include <Common/MainFrame.hpp>

namespace common
{
	class App
	{
	protected:
		App(const std::string &name);

	public:
		virtual ~App() = default;
		void init();
		void exit();

		void updateFps(std::chrono::microseconds const & durationGpu
			, std::chrono::microseconds const & durationCpu);
		void updateFps(std::chrono::microseconds & duration);

	private:
		virtual std::unique_ptr<MainFrame> doCreateMainFrame() = 0;

	protected:
		std::string m_name;
		bool m_allocated{ false };
		std::unique_ptr<MainFrame> m_mainFrame;
	};
}