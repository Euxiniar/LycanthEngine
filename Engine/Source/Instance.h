#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <ValidationLayers.h>
#include <Extensions.h>
#include <memory>

namespace Ly {
	class Instance {
	public:
		Instance(const char* appName, const char* engineName, std::vector<const char*> validationLayers);
		~Instance();
		VkInstance& get();
		
	private:
		VkInstance m_instance;
		
		void createInstance(const char * appName, const char * engineName, std::vector<const char*>& validationLayers);
	};
}
