#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>

namespace Ly {
	class Sampler {
	public:
		Sampler(VkDevice& device);
		~Sampler();
		VkSampler& get();
	private:
		VkSampler m_sampler;
		VkDevice& m_device;
		void create();
	};
}