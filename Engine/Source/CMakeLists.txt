set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(BASE
	
    PARENT_SCOPE
)

set(CMAKE_TEXT
    ${DIR}/CMakeLists.txt
	${DIR}/LycanthPrerequisites.hpp
    PARENT_SCOPE
)

set(COMMON
	${DIR}/Common/Application.cpp
	${DIR}/Common/Application.hpp
	${DIR}/Common/MainFrame.cpp
	${DIR}/Common/MainFrame.hpp
	${DIR}/Common/Prerequisites.hpp
	PARENT_SCOPE
)

set(CORE
	${DIR}/Core/Renderer.cpp
	${DIR}/Core/Renderer.hpp
	PARENT_SCOPE
)