#pragma once 
#include <memory>
#include <Core/Renderer.hpp>

namespace Ly 
{
	using RendererPtr = std::unique_ptr< Renderer >;
}