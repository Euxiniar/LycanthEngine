#include <DebugCallback.h>

namespace Ly {
	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType,
		uint64_t obj, size_t location, int32_t code, const char * layerPrefix, const char * msg, void * userData)
	{
		Ly::Log::debug("validation layer: ");
		Ly::Log::debug(msg);

		return VK_FALSE;
	}

	DebugCallback::DebugCallback(VkInstance & instance)
		: m_instance(instance)
	{
		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		if (createDebugReportCallbackEXT(m_instance, &createInfo, nullptr, &m_callback) != VK_SUCCESS) {
			Ly::Log::error("Failed to set up debug callback !");
		}
	}

	DebugCallback::~DebugCallback()
	{
		destroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
	}

	VkResult DebugCallback::createDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DebugCallback::destroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}
}