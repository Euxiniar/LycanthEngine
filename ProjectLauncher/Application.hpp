#pragma once
#include <Common/Application.hpp>
#include "Prerequisites.hpp"

namespace vkapp
{
	class Application : public common::App
	{
	public:
		Application();
	private:
		std::unique_ptr<common::MainFrame> doCreateMainFrame()override;
	};
}