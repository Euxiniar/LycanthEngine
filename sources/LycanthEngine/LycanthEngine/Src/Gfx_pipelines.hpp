#pragma once
#include "Renderer.hpp"
#include "Swapchain.hpp"
#include "Shaders.hpp"
#include "Mesh.hpp"
#include "Descriptor_Set_Group.hpp"
#include <misc/render_pass_create_info.h>
#include <wrappers/render_pass.h>
#include <wrappers/swapchain.h>
#include <wrappers/graphics_pipeline_manager.h>

namespace Ly
{
	class Gfx_pipelines
	{
	public:
		static std::unique_ptr<Ly::Gfx_pipelines> create(Ly::Renderer& renderer, Ly::Swapchain& swapchain, Ly::Descriptor_Set_Group& dsg, Ly::Shaders& shaders);
		Gfx_pipelines(Ly::Renderer& renderer, Ly::Swapchain& swapchain, Ly::Descriptor_Set_Group& dsg, Ly::Shaders& shaders);
	private:
		Anvil::RenderPassUniquePtr m_renderpass_ptr;
		Anvil::PipelineID m_pipeline_id;
	};
}