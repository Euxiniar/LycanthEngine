set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(BASE
    ${DIR}/Renderer.h
    ${DIR}/Renderer.cpp
	${DIR}/VulkanLoader.h
    ${DIR}/VulkanLoader.cpp
    ${DIR}/Window.h
    ${DIR}/Window.cpp
	${DIR}/DebugCallback.h
    ${DIR}/DebugCallback.cpp
	${DIR}/Instance.h
	${DIR}/Instance.cpp
	${DIR}/ValidationLayers.h
	${DIR}/ValidationLayers.cpp
	${DIR}/Extensions.h
	${DIR}/Extensions.cpp
	${DIR}/PhysicalDevice.h
	${DIR}/PhysicalDevice.cpp
	${DIR}/QueueFamily.h
	${DIR}/QueueFamily.cpp
	${DIR}/Swapchain.h
	${DIR}/Swapchain.cpp
	${DIR}/LogicalDevice.h
	${DIR}/LogicalDevice.cpp
	${DIR}/ImageViews.h
	${DIR}/ImageViews.cpp
    PARENT_SCOPE
)

set(UTILS
    ${DIR}/Utils/Log.h
    ${DIR}/Utils/Log.cpp
    PARENT_SCOPE
)

set(CMAKE_TEXT
    ${DIR}/CMakeLists.txt
    PARENT_SCOPE
)
list(APPEND ENGINE_SOURCES
    ${BASE}
    ${UTILS}
	${CMAKE_TEXT}
)