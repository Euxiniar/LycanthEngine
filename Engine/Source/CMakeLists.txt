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
	PARENT_SCOPE
)

SET(VULKAN_LOADER
	${DIR}/VulkanLoader.h
    ${DIR}/VulkanLoader.cpp
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

set(CMAKE_TEXT
    ${DIR}/CMakeLists.txt
    PARENT_SCOPE
)