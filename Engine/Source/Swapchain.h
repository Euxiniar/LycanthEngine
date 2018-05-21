#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>
#include <algorithm>
#include <Window.h>
#include <QueueFamily.h>
#include <memory>

namespace Ly {
	struct SwapChainSupportDetails {
		//Min/Max number of images in the swapchain
		//Min/Max images size in the swapchain
		VkSurfaceCapabilitiesKHR capabilities;
		//Pixel Format/Color Space
		std::vector<VkSurfaceFormatKHR> formats;
		//Image resolution in the swapchain
		std::vector<VkPresentModeKHR> presentModes;
	};

	class Swapchain {
	public:
		Swapchain(std::unique_ptr<Ly::Window>& window,
		VkPhysicalDevice& physicalDevice,
		VkSurfaceKHR& surface,
		VkDevice& device,
		std::vector<VkImage>& swapChainImages,
		VkFormat& swapChainImageFormat,
		VkExtent2D& swapChainExtent);
		~Swapchain();
		VkSwapchainKHR& get();

		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

	private:
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities);
		void create();

		std::unique_ptr<Ly::Window>& m_window;
		VkPhysicalDevice& m_physicalDevice;
		VkSurfaceKHR& m_surface;
		VkDevice& m_device;
		std::vector<VkImage>& m_swapChainImages;
		VkFormat& m_swapChainImageFormat;
		VkExtent2D& m_swapChainExtent;

		VkSwapchainKHR m_swapChain;
	};
}
