#include <ImageViews.h>

namespace Ly {
	ImageViews::ImageViews(VkDevice & device, std::vector<VkImage>& swapChainImages, VkFormat & swapChainImageFormat)
		: m_device(device), m_swapChainImages(swapChainImages), m_swapChainImageFormat(swapChainImageFormat)
	{
		create();
	}

	ImageViews::~ImageViews()
	{
		for (int i = 0; i < m_swapChainImageViews.size(); i++) {
			m_swapChainImageViews[i].reset();
		}
	}

	std::vector<std::unique_ptr<Ly::ImageView>>& ImageViews::get()
	{
		return m_swapChainImageViews;
	}

	void ImageViews::create()
	{
		for (size_t i = 0; i < m_swapChainImages.size(); i++) {
			m_swapChainImageViews.push_back(std::make_unique<Ly::ImageView>(m_device, 
				m_swapChainImages[i], m_swapChainImageFormat));
		}
	}
}
