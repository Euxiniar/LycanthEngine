#pragma once
#include <vulkan\vulkan.h>
#include <Utils/Log.h>
#include <string>

namespace Ly {
	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData);

	class DebugCallback {
	public:
		DebugCallback(VkInstance & instance);
		~DebugCallback();
		VkResult createDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
		void destroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, 
			const VkAllocationCallbacks* pAllocator);
	private:
		VkInstance& m_instance;
		VkDebugReportCallbackEXT m_callback;
	};
}