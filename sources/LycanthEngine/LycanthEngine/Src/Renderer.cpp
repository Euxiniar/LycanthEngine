#include "Renderer.hpp"

namespace Ly
{
	Renderer::Renderer(std::string app_name, std::string engine_name, bool enable_validation)
	{
		m_instance_ptr = Anvil::Instance::create(app_name,
			engine_name,
#ifdef ENABLE_VALIDATION
			std::bind(&Renderer::on_validation_callback,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4),
#else
			Anvil::DebugCallbackFunction(),
#endif
				false); 

		m_physical_device_ptr = m_instance_ptr->get_physical_device(0);

		/* Create a Vulkan device */
		m_device_ptr = Anvil::SGPUDevice::create(m_physical_device_ptr,
			true,
			Anvil::DeviceExtensionConfiguration(),
			std::vector<std::string>(), 
			false,
			false);
	}

	Renderer::~Renderer()
	{
	}

	std::unique_ptr<Ly::Renderer> Renderer::create(std::string app_name, std::string engine_name, bool enable_validation)
	{
		return std::unique_ptr<Ly::Renderer>(new Renderer(app_name, engine_name, enable_validation));
	}

	VkBool32 Renderer::on_validation_callback(VkDebugReportFlagsEXT      in_message_flags,
		VkDebugReportObjectTypeEXT in_object_type,
		const char*                in_layer_prefix,
		const char*                in_message)
	{
		if ((in_message_flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
		{
			fprintf(stderr,
				"[!] %s\n",
				in_message);
		}

		return false;
	}

	Anvil::BaseDeviceUniquePtr* Renderer::get_device()
	{
		return &m_device_ptr;
	}

	Anvil::InstanceUniquePtr* Renderer::get_instance()
	{
		return &m_instance_ptr;
	}

}