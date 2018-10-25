project(Game)

include_directories( 
	${CMAKE_BINARY_DIR}/deps/anvil/include
	${CMAKE_SOURCE_DIR}/deps/anvil/include
	${CMAKE_BINARY_DIR}/sources/LycanthEngine/LycanthEngine/Src
	${CMAKE_SOURCE_DIR}/sources/LycanthEngine/LycanthEngine/Src
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

add_dependencies (${PROJECT_NAME} LycanthEngine)

#----------------------Links Project----------------------#

target_link_libraries(${PROJECT_NAME} LycanthEngine)

if(WIN32)
   set_target_properties(${PROJECT_NAME} PROPERTIES 
	LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE" 
	LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
endif(WIN32)