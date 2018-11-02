#pragma once
#include <wrappers/descriptor_set_group.h>
#include <memory>
#include "Buffers.hpp"
#include "Renderer.hpp"

namespace Ly
{
	class Descriptor_Set_Group
	{
	public:
		static std::unique_ptr<Descriptor_Set_Group> create(Ly::Renderer& renderer, Ly::Buffers& buffers);
		Descriptor_Set_Group(Ly::Renderer& renderer, Ly::Buffers& buffers);
		~Descriptor_Set_Group();
		Anvil::DescriptorSetGroupUniquePtr& get_dsg();

	private:
		Anvil::DescriptorSetGroupUniquePtr m_dsg_ptr;
	};
}