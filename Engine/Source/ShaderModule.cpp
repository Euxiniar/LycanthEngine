#include <ShaderModule.h>

namespace Ly {
	ShaderModule::ShaderModule(const std::vector<char>& code, VkDevice & device)
		: m_code(code), m_device(device)
	{
		create();
	}

	ShaderModule::~ShaderModule()
	{
		vkDestroyShaderModule(m_device, m_shaderModule, nullptr);
	}

	VkShaderModule & ShaderModule::get()
	{
		return m_shaderModule;
	}

	void ShaderModule::create() {
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = m_code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(m_code.data());

		if (vkCreateShaderModule(m_device, &createInfo, nullptr, &m_shaderModule) != VK_SUCCESS) {
			Ly::Log::error("failed to create shader module!");
		}
	}
}
