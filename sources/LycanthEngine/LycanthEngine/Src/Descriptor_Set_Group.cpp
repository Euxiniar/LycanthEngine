#include "Descriptor_Set_Group.hpp"

namespace Ly
{
	std::unique_ptr<Descriptor_Set_Group> Descriptor_Set_Group::create(Ly::Renderer & renderer, Ly::Buffers & buffers)
	{
		return std::unique_ptr<Ly::Descriptor_Set_Group>(new Descriptor_Set_Group(renderer, buffers));
	}

	Descriptor_Set_Group::Descriptor_Set_Group(Ly::Renderer& renderer, Ly::Buffers& buffers)
	{
		{
		auto dsg_create_info_ptrs = std::vector<Anvil::DescriptorSetCreateInfoUniquePtr>(1);

		dsg_create_info_ptrs[0] = Anvil::DescriptorSetCreateInfo::create();

		dsg_create_info_ptrs[0]->add_binding(0, /* n_binding */
			Anvil::DescriptorType::UNIFORM_BUFFER_DYNAMIC,
			1, /* n_elements */
			Anvil::ShaderStageFlagBits::VERTEX_BIT);

		m_dsg_ptr = Anvil::DescriptorSetGroup::create(renderer.get_device()->get(),
			dsg_create_info_ptrs,
			false); /* releaseable_sets */
		}

	m_dsg_ptr->set_binding_item(0, /* n_set     */
		0, /* n_binding */
		Anvil::DescriptorSet::DynamicUniformBufferBindingElement(buffers.get_data_buffer_ptr().get(),
			0, /* in_start_offset */
			buffers.get_ub_data_size_per_swapchain_image()));
	}

	Descriptor_Set_Group::~Descriptor_Set_Group()
	{
	}

	Anvil::DescriptorSetGroupUniquePtr& Descriptor_Set_Group::get_dsg()
	{
		return m_dsg_ptr;
	}

}