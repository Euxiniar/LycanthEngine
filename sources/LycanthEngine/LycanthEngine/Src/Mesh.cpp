#include "Mesh.hpp"

namespace Ly
{
	const unsigned char* Mesh::get_mesh_data() const
	{
		return reinterpret_cast<const unsigned char*>(g_mesh_data.data());
	}

	Anvil::Format Mesh::get_mesh_data_color_format()
	{
		return Anvil::Format::R32G32B32_SFLOAT;
	}

	uint32_t Mesh::get_mesh_data_color_start_offset()
	{
		return g_mesh_data_color_start_offset;
	}

	uint32_t Mesh::get_mesh_data_color_stride()
	{
		return g_mesh_data_color_stride;
	}

	Anvil::Format Mesh::get_mesh_data_position_format()
	{
		return Anvil::Format::R32G32B32A32_SFLOAT;
	}

	uint32_t Mesh::get_mesh_data_position_start_offset()
	{
		return g_mesh_data_position_start_offset;
	}

	uint32_t Mesh::get_mesh_data_position_stride()
	{
		return g_mesh_data_position_stride;
	}

	uint32_t Mesh::get_mesh_data_size() const
	{
		return sizeof(g_mesh_data.data());
	}

	uint32_t Mesh::get_mesh_n_vertices()
	{
		return g_mesh_data_n_vertices;
	}

	void Mesh::get_luminance_data(std::unique_ptr<float[]>* out_result_ptr,
		uint32_t*                 out_result_size_ptr)
	{
		std::unique_ptr<float[]> luminance_data_ptr;
		float*                   luminance_data_raw_ptr;
		uint32_t                 luminance_data_size;

		static_assert(N_TRIANGLES == 16,
			"Shader and the app logic assumes N_TRIANGLES will always be 16");

		luminance_data_size = sizeof(float) * N_TRIANGLES;

		luminance_data_ptr.reset(new float[luminance_data_size / sizeof(float)]);

		luminance_data_raw_ptr = luminance_data_ptr.get();

		for (uint32_t n_tri = 0;
			n_tri < N_TRIANGLES;
			++n_tri)
		{
			luminance_data_raw_ptr[n_tri] = float(n_tri) / float(N_TRIANGLES - 1);
		}

		*out_result_ptr = std::move(luminance_data_ptr);
		*out_result_size_ptr = luminance_data_size;
	}
}