#include "Framebuffers.hpp"

namespace Ly
{
	std::unique_ptr<Ly::Framebuffers> Framebuffers::create(Ly::Renderer & renderer, Ly::Swapchain & swapchain)
	{
		return std::unique_ptr<Ly::Framebuffers>(new Framebuffers(renderer, swapchain));
	}

	Framebuffers::Framebuffers(Ly::Renderer& renderer, Ly::Swapchain& swapchain)
	{
		bool result;

		/* We need to instantiate 1 framebuffer object per each used swap-chain image */
		for (uint32_t n_fbo = 0;
			n_fbo < N_SWAPCHAIN_IMAGES;
			++n_fbo)
		{
			Anvil::ImageView* attachment_image_view_ptr = nullptr;

			attachment_image_view_ptr = swapchain.get_swapchain()->get_image_view(n_fbo);

			/* Create the internal framebuffer object */
			{
				auto create_info_ptr = Anvil::FramebufferCreateInfo::create(renderer.get_device()->get(),
					1280,
					720,
					1 /* n_layers */);

				result = create_info_ptr->add_attachment(attachment_image_view_ptr,
					nullptr /* out_opt_attachment_id_ptr */);
				anvil_assert(result);

				m_fbos[n_fbo] = Anvil::Framebuffer::create(std::move(create_info_ptr));
			}

			m_fbos[n_fbo]->set_name_formatted("Framebuffer for swapchain image [%d]",
				n_fbo);
		}
	}

}