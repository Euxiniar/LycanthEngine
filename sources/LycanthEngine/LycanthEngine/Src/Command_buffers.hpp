#pragma once
#include "Renderer.hpp"

namespace Ly
{
	class Command_buffers
	{
	public :
		Command_buffers(Ly::Renderer& renderer);
		~Command_buffers();
	};
}