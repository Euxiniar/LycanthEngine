#pragma once
#include "Renderer.hpp"
#include "Prerequisites.hpp"
#include <wrappers/shader_module.h>
#include <misc/glsl_to_spirv.h>

namespace Ly
{
	class Shaders
	{
	public:
		static std::unique_ptr<Ly::Shaders> create(Ly::Renderer& renderer);
		Shaders(Ly::Renderer& renderer);
	private:
		std::unique_ptr<Anvil::ShaderModuleStageEntryPoint> m_fs_ptr;
		std::unique_ptr<Anvil::ShaderModuleStageEntryPoint> m_vs_ptr;

		static const char* g_glsl_frag;
		static const char* g_glsl_vert;
	}; 
}