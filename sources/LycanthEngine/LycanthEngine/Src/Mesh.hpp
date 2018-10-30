#pragma once
#include <cstdint>
#include <misc/formats.h>
#include <array>

namespace Ly
{
	class Mesh
	{
	public:
		const unsigned char* get_mesh_data() const;
		static Anvil::Format get_mesh_data_color_format();
		static uint32_t get_mesh_data_color_start_offset();
		static uint32_t get_mesh_data_color_stride();
		static Anvil::Format get_mesh_data_position_format();
		static uint32_t get_mesh_data_position_start_offset();
		static uint32_t get_mesh_data_position_stride();
		uint32_t get_mesh_data_size() const;
		static uint32_t Mesh::get_mesh_n_vertices();

	private:
		const std::array<float, 21> g_mesh_data =
		{
		   -1.0f,  1.0f,  0.0f, 1.0f,   /* position */
			0.75f, 0.25f, 0.1f,         /* color    */

		   -1.0f, -1.0f,  0.0f, 1.0f,   /* position */
			0.25f, 0.75f, 0.2f,         /* color    */

			1.0f, -1.0f,  0.0f, 1.0f,   /* position */
			0.1f,  0.3f,  0.5f,         /* color    */
		};

		static const uint32_t g_mesh_data_color_start_offset = sizeof(float) * 4;
		static const uint32_t g_mesh_data_color_stride = sizeof(float) * 7;
		static const uint32_t g_mesh_data_n_vertices = 3;
		static const uint32_t g_mesh_data_position_start_offset = 0;
		static const uint32_t g_mesh_data_position_stride = sizeof(float) * 7;
	};
}