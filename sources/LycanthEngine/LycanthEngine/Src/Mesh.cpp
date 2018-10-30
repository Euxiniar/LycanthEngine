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
}