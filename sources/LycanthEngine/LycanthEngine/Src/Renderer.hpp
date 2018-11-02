#pragma once
#include <string>
#include <memory>

#include <wrappers/instance.h>
#include <wrappers/physical_device.h>
#include <wrappers/device.h>
#include "Prerequisites.hpp"

namespace Ly
{
	class Application;

	class Renderer
	{
	public:
		static std::unique_ptr<Renderer> create(std::string app_name, std::string engine_name, bool enable_validation);
		Renderer(std::string app_name, std::string engine_name, bool enable_validation);
		~Renderer();
		Anvil::BaseDeviceUniquePtr* get_device();
		Anvil::InstanceUniquePtr* get_instance();

	private:
		Anvil::InstanceUniquePtr m_instance_ptr;
		const Anvil::PhysicalDevice* m_physical_device_ptr;
		Anvil::BaseDeviceUniquePtr m_device_ptr;
		VkBool32 on_validation_callback(VkDebugReportFlagsEXT in_message_flags, 
			VkDebugReportObjectTypeEXT in_object_type, const char * in_layer_prefix, const char * in_message);
	};
}