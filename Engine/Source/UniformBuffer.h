#pragma once
#include <vulkan/vulkan.h>
#include <Buffer.h>
#include <UniformBufferObject.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

namespace Ly {
	class UniformBuffer : public Buffer {
	public:
		UniformBuffer(VkDevice &device,
			VkPhysicalDevice &physicalDevice,
			VkDeviceSize size);
		~UniformBuffer();
		void update(uint32_t widthPerspective, 
			uint32_t heightPerspective);
	};
}