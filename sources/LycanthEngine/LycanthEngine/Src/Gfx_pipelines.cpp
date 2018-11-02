#include "Gfx_pipelines.hpp"

namespace Ly
{

	std::unique_ptr<Ly::Gfx_pipelines> Gfx_pipelines::create(Ly::Renderer& renderer, Ly::Swapchain& swapchain, Ly::Descriptor_Set_Group& dsg, Ly::Shaders& shaders)
	{
		return std::unique_ptr<Ly::Gfx_pipelines>(new Ly::Gfx_pipelines(renderer, swapchain, dsg, shaders));
	}

	Gfx_pipelines::Gfx_pipelines(Ly::Renderer & renderer, Ly::Swapchain& swapchain, Ly::Descriptor_Set_Group& dsg, Ly::Shaders& shaders)
	: m_renderer(renderer)
	{
		Anvil::GraphicsPipelineCreateInfoUniquePtr gfx_pipeline_create_info_ptr;
		auto                                       gfx_pipeline_manager_ptr(renderer.get_device()->get()->get_graphics_pipeline_manager());

		/* Create a renderpass for the pipeline */
		Anvil::RenderPassAttachmentID render_pass_color_attachment_id;
		Anvil::SubPassID              render_pass_subpass_id;

		{
			Anvil::RenderPassCreateInfoUniquePtr render_pass_create_info_ptr(new Anvil::RenderPassCreateInfo(renderer.get_device()->get()));
			render_pass_create_info_ptr->add_color_attachment(swapchain.get_swapchain()->get_create_info_ptr()->get_format(),
				Anvil::SampleCountFlagBits::_1_BIT,
				Anvil::AttachmentLoadOp::CLEAR,
				Anvil::AttachmentStoreOp::STORE,
				Anvil::ImageLayout::COLOR_ATTACHMENT_OPTIMAL,
#ifdef ENABLE_OFFSCREEN_RENDERING
				Anvil::ImageLayout::GENERAL,
#else
				Anvil::ImageLayout::PRESENT_SRC_KHR,
#endif
				false, /* may_alias */
				&render_pass_color_attachment_id);


			render_pass_create_info_ptr->add_subpass(&render_pass_subpass_id);
			render_pass_create_info_ptr->add_subpass_color_attachment(render_pass_subpass_id,
				Anvil::ImageLayout::COLOR_ATTACHMENT_OPTIMAL,
				render_pass_color_attachment_id,
				0,        /* location                      */
				nullptr); /* opt_attachment_resolve_id_ptr */


			m_renderpass_ptr = Anvil::RenderPass::create(std::move(render_pass_create_info_ptr),
				swapchain.get_swapchain().get());
		}

		m_renderpass_ptr->set_name("Main renderpass");

		gfx_pipeline_create_info_ptr = Anvil::GraphicsPipelineCreateInfo::create(Anvil::PipelineCreateFlagBits::NONE,
			m_renderpass_ptr.get(),
			render_pass_subpass_id,
			*shaders.get_fragment_shader(),
			Anvil::ShaderModuleStageEntryPoint(), /* in_geometry_shader        */
			Anvil::ShaderModuleStageEntryPoint(), /* in_tess_control_shader    */
			Anvil::ShaderModuleStageEntryPoint(), /* in_tess_evaluation_shader */
			*shaders.get_vertex_shader());



		gfx_pipeline_create_info_ptr->set_descriptor_set_create_info(dsg.get_dsg()->get_descriptor_set_create_info());
		gfx_pipeline_create_info_ptr->attach_push_constant_range(0, /* in_offset */
			sizeof(float) * 4 /* vec4 */ * 4 /* vec4 values */,
			Anvil::ShaderStageFlagBits::FRAGMENT_BIT | Anvil::ShaderStageFlagBits::VERTEX_BIT);
		gfx_pipeline_create_info_ptr->set_rasterization_properties(Anvil::PolygonMode::FILL,
			Anvil::CullModeFlagBits::NONE,
			Anvil::FrontFace::COUNTER_CLOCKWISE,
			1.0f); /* in_line_width       */
		gfx_pipeline_create_info_ptr->set_color_blend_attachment_properties(0,     /* in_attachment_id    */
			true,  /* in_blending_enabled */
			Anvil::BlendOp::ADD,
			Anvil::BlendOp::ADD,
			Anvil::BlendFactor::SRC_ALPHA,
			Anvil::BlendFactor::ONE_MINUS_SRC_ALPHA,
			Anvil::BlendFactor::SRC_ALPHA,
			Anvil::BlendFactor::ONE_MINUS_SRC_ALPHA,
			Anvil::ColorComponentFlagBits::A_BIT | Anvil::ColorComponentFlagBits::B_BIT | Anvil::ColorComponentFlagBits::G_BIT | Anvil::ColorComponentFlagBits::R_BIT);

		gfx_pipeline_create_info_ptr->add_vertex_attribute(0, /* in_location */
			Mesh::get_mesh_data_position_format(),
			Mesh::get_mesh_data_position_start_offset(),
			Mesh::get_mesh_data_position_stride(),
			Anvil::VertexInputRate::VERTEX);
		gfx_pipeline_create_info_ptr->add_vertex_attribute(1, /* location */
			Mesh::get_mesh_data_color_format(),
			Mesh::get_mesh_data_color_start_offset(),
			Mesh::get_mesh_data_color_stride(),
			Anvil::VertexInputRate::VERTEX);


		gfx_pipeline_manager_ptr->add_pipeline(std::move(gfx_pipeline_create_info_ptr),
			&m_pipeline_id);
	}

	Gfx_pipelines::~Gfx_pipelines()
	{
		m_renderpass_ptr.reset();
	}

	Anvil::RenderPassUniquePtr& Gfx_pipelines::get_renderPass()
	{
		return m_renderpass_ptr;
	}

	Anvil::PipelineID& Gfx_pipelines::get_pipeline_id()
	{
		return m_pipeline_id;
	}

	void Gfx_pipelines::set_pipeline_id(uint32_t value)
	{
		m_pipeline_id = value;
	}

}