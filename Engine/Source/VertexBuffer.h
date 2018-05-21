#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <Vertex.hpp>
#include <vector>

#include <Buffer.h>

namespace Ly {
	class VertexBuffer : public Buffer {
	private:
		void create();

		const std::vector<Vertex>& m_vertices;
		VkDeviceSize m_bufferSize;

	public:
		VertexBuffer(VkDevice& device, VkPhysicalDevice& physicalDevice, const std::vector<Vertex>& vertices);
		~VertexBuffer();
	};
}
