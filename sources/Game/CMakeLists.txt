project(Game)

if (WIN32)
    include_directories($ENV{VK_SDK_PATH}/Include
                        $ENV{VULKAN_SDK}/Include)
    
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
            link_directories   ($ENV{VK_SDK_PATH}/Bin
                                $ENV{VK_SDK_PATH}/Lib
                                $ENV{VULKAN_SDK}/Bin
                                $ENV{VULKAN_SDK}/Lib)
    else()
            link_directories   ($ENV{VK_SDK_PATH}/Bin32
                                $ENV{VK_SDK_PATH}/Lib32
                                $ENV{VULKAN_SDK}/Bin32
                                $ENV{VULKAN_SDK}/Lib32)
    endif()
else()
    include_directories($ENV{VK_SDK_PATH}/x86_64/include
                        $ENV{VULKAN_SDK}/include
                        $ENV{VULKAN_SDK}/x86_64/include)
    link_directories   ($ENV{VK_SDK_PATH}/x86_64/lib
                        $ENV{VULKAN_SDK}/lib
                        $ENV{VULKAN_SDK}/x86_64/lib)
endif()
include_directories( 
	${DEPS}/anvil/include
	${CMAKE_BINARY_DIR}/deps/anvil/include
)

file( GLOB_RECURSE ${PROJECT_NAME}_FILES
	Src/*.c
	Src/*.cpp
	Src/*.h
	Src/*.hpp
)

if(WIN32)
add_executable(${PROJECT_NAME} WIN32
	${${PROJECT_NAME}_FILES}
)
endif(WIN32)

add_dependencies (${PROJECT_NAME} Anvil)

#----------------------Links Project----------------------#

target_link_libraries(${PROJECT_NAME} Anvil)

if(WIN32)
   set_target_properties(${PROJECT_NAME} PROPERTIES 
	LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE" 
	LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
endif(WIN32)