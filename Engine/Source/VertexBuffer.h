#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <Vertex.hpp>
#include <vector>

namespace Ly {
	class VertexBuffer {
	public:
		VertexBuffer(VkDevice& device, VkPhysicalDevice& physicalDevice, const std::vector<Vertex>& vertices);
		~VertexBuffer();

		VkBuffer& get();

	private:
		VkBuffer m_vertexBuffer;
		VkDeviceMemory m_vertexBufferMemory;

		void create();

		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

		VkDevice& m_device;
		VkPhysicalDevice& m_physicalDevice;
		const std::vector<Vertex>& m_vertices;
	};
}
