#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <Utils/Log.h>

namespace Ly {
	class ShaderModule {
	public:
		ShaderModule(const std::vector<char>& code, VkDevice& device);
		~ShaderModule();
		VkShaderModule& get();

	private:
		void create();
		VkShaderModule m_shaderModule;

		const std::vector<char>& m_code;
		VkDevice& m_device;
	};
}
