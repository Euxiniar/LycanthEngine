#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Window.h>
#include <DebugCallback.h>
#include <Utils/Log.h>

#include <memory>
#include <vector>
#include <set>
#include <algorithm>

namespace Ly {
	struct QueueFamilyIndices {
		//Queue Family wich supports graphics
		int graphicsFamily = -1;
		//Queue Family wich supports display presentation
		int presentFamily = -1;

		bool matches() {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	struct SwapChainSupportDetails {
		//Min/Max number of images in the swapchain
		//Min/Max images size in the swapchain
		VkSurfaceCapabilitiesKHR capabilities;
		//Pixel Format/Color Space
		std::vector<VkSurfaceFormatKHR> formats;
		//Image resolution in the swapchain
		std::vector<VkPresentModeKHR> presentModes;
	};

	class VulkanLoader
	{
	public:
		VulkanLoader(std::unique_ptr<Window>& window);
		~VulkanLoader();

	private:
		void initVulkan();
		void createInstance();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		void setupDebugCallback();
		void createSurface();
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void createLogicalDevice();
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void createSwapChain();


		const std::vector<const char*> m_validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
		};
#ifdef NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif

		const std::vector<const char*> m_deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		std::unique_ptr<Ly::Window>& m_window;
		VkInstance m_instance;
		std::string m_appName = "Vulkan";
		std::string m_engineName = "LycanthEngine";
		std::unique_ptr<Ly::DebugCallback> m_callback;
		VkSurfaceKHR m_surface;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		VkSwapchainKHR m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		VkFormat m_swapChainImagesFormat;
		VkExtent2D m_swapChainExtent;
	};
}