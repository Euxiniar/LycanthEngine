cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#----------------------Project----------------------#
set(PROJECT "FirstProject")
project (${PROJECT})

if(WIN32)
add_executable(${PROJECT} WIN32
    ProjectLauncher/Application.cpp
)
endif(WIN32)

#----------------------Engine----------------------#
set(ENGINE "LycanthEngine")
project (${ENGINE})

add_subdirectory(Engine/Source)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Engine/Source)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Includes/)

find_package (Vulkan REQUIRED)
if (Vulkan_FOUND)
  include_directories(${Vulkan_INCLUDE_DIRS})
  target_link_libraries (${PROJECT} ${Vulkan_LIBRARIES})
endif ()

set(SHADERS
     ${CMAKE_SOURCE_DIR}/Data/Shaders/frag.spv
	 ${CMAKE_SOURCE_DIR}/Data/Shaders/vert.spv
	 ${CMAKE_SOURCE_DIR}/Data/Shaders/shader.frag
	 ${CMAKE_SOURCE_DIR}/Data/Shaders/shader.vert
	 ${CMAKE_SOURCE_DIR}/Data/Shaders/compile.bat
	)

add_library(${ENGINE} STATIC
    ${BASE}
	${RENDERER}
	${WINDOW}
	${INSTANCE}
	${PHYSICAL_DEVICE}
	${LOGICAL_DEVICE}
	${COMMAND_POOL}
	${VULKAN_LOADER}
	${UTILS}
	${CMAKE_TEXT}
	${SHADERS}
	${SWAPCHAIN}
	${SYNC_OBJECT}
	${SHADER_MODULE}
	${RENDER_PASS}
	${QUEUE_FAMILY}
	${GRAPHICS_PIPELINE}
	${PIPELINE_LAYOUT}
	${BUFFER}
	${VERTEX_BUFFER}
)

source_group( Shaders FILES ${SHADERS})

source_group( Engine FILES ${BASE})
source_group( Engine\\Renderer FILES ${RENDERER})
source_group( Engine\\Window FILES ${WINDOW})
source_group( Engine\\Instance FILES ${INSTANCE})
source_group( Engine\\Physical_Device FILES ${PHYSICAL_DEVICE})
source_group( Engine\\Logical_Device FILES ${LOGICAL_DEVICE})
source_group( Engine\\Command_Pool FILES ${COMMAND_POOL})
source_group( Engine\\Vulkan_Loader FILES ${VULKAN_LOADER})
source_group( Engine\\Utils FILES ${UTILS})
source_group( Engine\\Swapchain FILES ${SWAPCHAIN})
source_group( Engine\\Sync_Object FILES ${SYNC_OBJECT})
source_group( Engine\\Shader_Module FILES ${SHADER_MODULE})
source_group( Engine\\Render_Pass FILES ${RENDER_PASS})
source_group( Engine\\Queue_Family FILES ${QUEUE_FAMILY})
source_group( Engine\\Graphics_Pipeline FILES ${GRAPHICS_PIPELINE})
source_group( Engine\\Pipeline_Layout FILES ${PIPELINE_LAYOUT})
source_group( Engine\\Buffer FILES ${BUFFER})
source_group( Engine\\Vertex_Buffer FILES ${VERTEX_BUFFER})



source_group( CMake FILES ${CMAKE_TEXT})

add_dependencies (${PROJECT} ${ENGINE})

#----------------------Links Project----------------------#

target_link_libraries(${PROJECT} debug ${CMAKE_BINARY_DIR}/Debug/LycanthEngine.lib)

target_link_libraries(${PROJECT} optimized ${CMAKE_BINARY_DIR}/Release/LycanthEngine.lib)

target_link_libraries(${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/glfw3.lib)

#----------------------Links Engine----------------------#
target_link_libraries(${ENGINE} ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/glfw3.lib)

if(WIN32)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W4")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4201")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4201")
		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrtd.lib")
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -Wall -Wundef -Wno-unused-parameter -Wno-missing-field-initializers")
	endif()
endif(WIN32)
message("Compiler is " ${CMAKE_CXX_COMPILER_ID})

if(WIN32)
   set_target_properties(${PROJECT} PROPERTIES 
	LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE" 
	LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
endif(WIN32)


add_custom_command(TARGET ${PROJECT} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Data ./Data)

add_custom_command(TARGET ${PROJECT} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Data ${CMAKE_BINARY_DIR}/Debug/Data)

add_custom_command(TARGET ${PROJECT} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Data ${CMAKE_BINARY_DIR}/Release/Data)

add_custom_command(TARGET ${PROJECT} PRE_BUILD 
	COMMAND cmd /c ${CMAKE_SOURCE_DIR}/Data/Shaders/compile.bat)