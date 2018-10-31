#include "Shaders.hpp"

namespace Ly
{
	const char* Ly::Shaders::g_glsl_frag =
		"#version 430\n"
		"\n"
		"layout (location = 0)      in  vec3 color;\n"
		"layout (location = 1) flat in  int  instance_id;\n"
		"layout (location = 0)      out vec4 result;\n"
		"\n"
		"layout (push_constant) uniform PCLuminance\n"
		"{\n"
		"    vec4 value0;\n"
		"    vec4 value1;\n"
		"    vec4 value2;\n"
		"    vec4 value3;\n"
		"} pcLuminance;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    int  index = instance_id / 4;\n"
		"    vec4 luminance;\n"
		"\n"
		"    result = vec4(color.xyz, 1.0);\n"
		"\n"
		"    if (index == 0)\n"
		"        luminance = pcLuminance.value0;\n"
		"    else if (index == 1)\n"
		"        luminance = pcLuminance.value1;\n"
		"    else if (index == 2)\n"
		"        luminance = pcLuminance.value2;\n"
		"    else if (index == 3)\n"
		"        luminance = pcLuminance.value3;\n"
		"\n"
		"    result.w = luminance[instance_id % 4];\n"
		"}\n";

	const char* Ly::Shaders::g_glsl_vert =
		"#version 430\n"
		"\n"
		"layout (location = 0) in vec4 vertexData;\n"
		"layout (location = 1) in vec3 colorData;\n"
		"\n"
		"layout (location = 0)      out vec3 result_color;\n"
		"layout (location = 1) flat out int  result_instance_id;\n"
		"\n"
		"layout (std140, binding = 0) uniform dataUB\n"
		"{\n"
		"    ivec4 frame_index;\n"
		"    vec4  position_rotation[N_TRIANGLES]; /* XY position, XY rotation */\n"
		"    vec4  size             [N_TRIANGLES / 4];\n"
		"};\n"
		"\n"
		"layout (push_constant) uniform PCLuminance\n"
		"{\n"
		"    vec4 value0;\n"
		"    vec4 value1;\n"
		"    vec4 value2;\n"
		"    vec4 value3;\n"
		"} pcLuminance;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    int  index = gl_InstanceIndex / 4;\n"
		"    vec4 luminance;\n"
		"\n"
		"    if (index == 0)\n"
		"        luminance = pcLuminance.value0;\n"
		"    else if (index == 1)\n"
		"        luminance = pcLuminance.value1;\n"
		"    else if (index == 2)\n"
		"        luminance = pcLuminance.value2;\n"
		"    else if (index == 3)\n"
		"        luminance = pcLuminance.value3;\n"
		"\n"
		"    result_color        = colorData + vec3(0.0, 0.0, 1.0 - luminance[gl_InstanceIndex % 4]);\n"
		"    result_instance_id  = gl_InstanceIndex;\n"
		"\n"
		"\n"
		"    vec4 result_position = vec4(vertexData.xy, 0.0, 1.0);\n"
		"    vec2 cos_factor      = cos(position_rotation[gl_InstanceIndex].zw);\n"
		"    vec2 sin_factor      = sin(position_rotation[gl_InstanceIndex].zw);\n"
		"\n"
		"    result_position.xy   = vec2(dot(vertexData.xy, vec2(cos_factor.x, -sin_factor.y) ),\n"
		"                                dot(vertexData.xy, vec2(sin_factor.x,  cos_factor.y) ));\n"
		"\n"
		"    switch (gl_InstanceIndex % 4)\n"
		"    {\n"
		"        case 0: result_position.xy *= vec2(size[index].x); break;\n"
		"        case 1: result_position.xy *= vec2(size[index].y); break;\n"
		"        case 2: result_position.xy *= vec2(size[index].z); break;\n"
		"        case 3: result_position.xy *= vec2(size[index].w); break;\n"
		"    }\n"
		"\n"
		"    result_position.xy += position_rotation[gl_InstanceIndex].xy;\n"
		"    gl_Position         = result_position;\n"
		"}\n";

	std::unique_ptr<Ly::Shaders> Shaders::create(Ly::Renderer& renderer)
	{
		return std::unique_ptr<Ly::Shaders>(new Ly::Shaders(renderer));
	}

	Shaders::Shaders(Ly::Renderer& renderer)
	{
		Anvil::GLSLShaderToSPIRVGeneratorUniquePtr fragment_shader_ptr;
		Anvil::ShaderModuleUniquePtr               fragment_shader_module_ptr;
		Anvil::GLSLShaderToSPIRVGeneratorUniquePtr vertex_shader_ptr;
		Anvil::ShaderModuleUniquePtr               vertex_shader_module_ptr;

		fragment_shader_ptr = Anvil::GLSLShaderToSPIRVGenerator::create(renderer.get_device()->get(),
			Anvil::GLSLShaderToSPIRVGenerator::MODE_USE_SPECIFIED_SOURCE,
			g_glsl_frag,
			Anvil::ShaderStage::FRAGMENT);
		vertex_shader_ptr = Anvil::GLSLShaderToSPIRVGenerator::create(renderer.get_device()->get(),
			Anvil::GLSLShaderToSPIRVGenerator::MODE_USE_SPECIFIED_SOURCE,
			g_glsl_vert,
			Anvil::ShaderStage::VERTEX);

		fragment_shader_ptr->add_definition_value_pair("N_TRIANGLES",
			N_TRIANGLES);
		vertex_shader_ptr->add_definition_value_pair("N_TRIANGLES",
			N_TRIANGLES);


		fragment_shader_module_ptr = Anvil::ShaderModule::create_from_spirv_generator(renderer.get_device()->get(),
			fragment_shader_ptr.get());
		vertex_shader_module_ptr = Anvil::ShaderModule::create_from_spirv_generator(renderer.get_device()->get(),
			vertex_shader_ptr.get());

		fragment_shader_module_ptr->set_name("Fragment shader module");
		vertex_shader_module_ptr->set_name("Vertex shader module");

		m_fs_ptr.reset(
			new Anvil::ShaderModuleStageEntryPoint("main",
				std::move(fragment_shader_module_ptr),
				Anvil::ShaderStage::FRAGMENT)
		);
		m_vs_ptr.reset(
			new Anvil::ShaderModuleStageEntryPoint("main",
				std::move(vertex_shader_module_ptr),
				Anvil::ShaderStage::VERTEX)
		);
	}
	std::unique_ptr<Anvil::ShaderModuleStageEntryPoint>& Shaders::get_fragment_shader()
	{
		return m_fs_ptr;
	}

	std::unique_ptr<Anvil::ShaderModuleStageEntryPoint>& Shaders::get_vertex_shader()
	{
		return m_vs_ptr;
	}

}
