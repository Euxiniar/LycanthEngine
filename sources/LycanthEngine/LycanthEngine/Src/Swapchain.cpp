#include "Swapchain.hpp"

namespace Ly
{

	std::unique_ptr<Ly::Swapchain> Swapchain::create(Ly::Renderer& renderer, Ly::Window& window)
	{
		return std::unique_ptr<Swapchain>(new Swapchain(renderer, window));
	}

	Swapchain::Swapchain(Ly::Renderer& renderer, Ly::Window& window)
		: m_n_swapchain_images(N_SWAPCHAIN_IMAGES)
	{
		Anvil::SGPUDevice* device_ptr(reinterpret_cast<Anvil::SGPUDevice*>(renderer.get_device()->get()));

		m_rendering_surface_ptr = Anvil::RenderingSurface::create(renderer.get_instance()->get(),
			renderer.get_device()->get(),
			window.get_window()->get());

		m_rendering_surface_ptr->set_name("Main rendering surface");


		m_swapchain_ptr = device_ptr->create_swapchain(m_rendering_surface_ptr.get(),
			window.get_window()->get(),
			Anvil::Format::B8G8R8A8_UNORM,
			Anvil::ColorSpaceKHR::SRGB_NONLINEAR_KHR,
			Anvil::PresentModeKHR::FIFO_KHR,
			Anvil::ImageUsageFlagBits::COLOR_ATTACHMENT_BIT,
			m_n_swapchain_images);

		m_swapchain_ptr->set_name("Main swapchain");

		/* Cache the queue we are going to use for presentation */
		const std::vector<uint32_t>* present_queue_fams_ptr = nullptr;

		if (!m_rendering_surface_ptr->get_queue_families_with_present_support(device_ptr->get_physical_device(),
			&present_queue_fams_ptr))
		{
			anvil_assert_fail();
		}

		m_present_queue_ptr = device_ptr->get_queue_for_queue_family_index(present_queue_fams_ptr->at(0),
			0); /* in_n_queue */
	}

	Swapchain::~Swapchain()
	{

	}

	Anvil::SwapchainUniquePtr& Swapchain::get_swapchain()
	{
		return m_swapchain_ptr;
	}

	uint32_t Swapchain::get_n_swapchain_images()
	{
		return m_n_swapchain_images;
	}

}