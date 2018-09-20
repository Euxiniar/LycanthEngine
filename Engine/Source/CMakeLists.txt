set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(BASE
	${DIR}/DebugCallback.h
    ${DIR}/DebugCallback.cpp
	${DIR}/ValidationLayers.h
	${DIR}/ValidationLayers.cpp
	${DIR}/Extensions.h
	${DIR}/Extensions.cpp
	${DIR}/ImageViews.h
	${DIR}/ImageViews.cpp
	${DIR}/Framebuffers.h
	${DIR}/Framebuffers.cpp
	${DIR}/CommandBuffers.h
	${DIR}/CommandBuffers.cpp
	${DIR}/Vertex.hpp
	${DIR}/UniformBufferObject.hpp
    PARENT_SCOPE
)

SET(RENDERER
	${DIR}/Renderer.h
    ${DIR}/Renderer.cpp
	PARENT_SCOPE
)

SET(WINDOW
	${DIR}/Window.h
    ${DIR}/Window.cpp
	PARENT_SCOPE
)

SET(INSTANCE
	${DIR}/Instance.h
	${DIR}/Instance.cpp
	PARENT_SCOPE
)

SET(PHYSICAL_DEVICE
	${DIR}/PhysicalDevice.h
	${DIR}/PhysicalDevice.cpp
	PARENT_SCOPE
)

SET(LOGICAL_DEVICE
	${DIR}/LogicalDevice.h
	${DIR}/LogicalDevice.cpp
	PARENT_SCOPE
)

SET(COMMAND_POOL
	${DIR}/CommandPool.h
	${DIR}/CommandPool.cpp
	${DIR}/Common/Prerequisites.hpp
	PARENT_SCOPE
)

SET(VULKAN_LOADER
	${DIR}/VulkanLoader.h
    ${DIR}/VulkanLoader.cpp
	${DIR}/Core/Renderer.hpp
	PARENT_SCOPE
)

set(UTILS
    ${DIR}/Utils/Log.h
    ${DIR}/Utils/Log.cpp
    PARENT_SCOPE
)

set(SWAPCHAIN
    ${DIR}/Swapchain.h
	${DIR}/Swapchain.cpp
    PARENT_SCOPE
)

set(SYNC_OBJECT
    ${DIR}/SyncObject.h
	${DIR}/SyncObject.cpp
    PARENT_SCOPE
)

set(SHADER_MODULE
	${DIR}/ShaderModule.h
	${DIR}/ShaderModule.cpp
    PARENT_SCOPE
)

set(RENDER_PASS
	${DIR}/RenderPass.h
	${DIR}/RenderPass.cpp
    PARENT_SCOPE
)

set(QUEUE_FAMILY
	${DIR}/QueueFamily.h
	${DIR}/QueueFamily.cpp
    PARENT_SCOPE
)

set(GRAPHICS_PIPELINE
	${DIR}/GraphicsPipeline.h
	${DIR}/GraphicsPipeline.cpp
    PARENT_SCOPE
)

set(PIPELINE_LAYOUT
	${DIR}/PipelineLayout.h
	${DIR}/PipelineLayout.cpp
    PARENT_SCOPE
)

set(DESCRIPTOR_SET_LAYOUT
	${DIR}/DescriptorSetLayout.h
	${DIR}/DescriptorSetLayout.cpp
    PARENT_SCOPE
)

set(BUFFER
	${DIR}/Buffer.h
	${DIR}/Buffer.cpp
    PARENT_SCOPE
)

set(VERTEX_BUFFER
	${DIR}/VertexBuffer.h
	${DIR}/VertexBuffer.cpp
    PARENT_SCOPE
)

set(INDEX_BUFFER
	${DIR}/IndexBuffer.h
	${DIR}/IndexBuffer.cpp
    PARENT_SCOPE
)

set(UNIFORM_BUFFER
	${DIR}/UniformBuffer.h
	${DIR}/UniformBuffer.cpp
    PARENT_SCOPE
)

set(DESCRIPTOR_POOL
	${DIR}/DescriptorPool.h
	${DIR}/DescriptorPool.cpp
    PARENT_SCOPE
)

set(IMAGE
	${DIR}/Image.h
)