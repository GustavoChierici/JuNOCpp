cmake_minimum_required(VERSION 3.0.0)
project(ArcherNOP VERSION 0.1.0)

include(FetchContent)
FetchContent_Declare(JuNOC++
	GIT_REPOSITORY https://github.com/GustavoChierici/JuNOCpp.git
	GIT_TAG master
)

FetchContent_GetProperties(JuNOC++)
if(NOT JuNOC++_POPULATED)
	FetchContent_MakeAvailable(JuNOC++)
endif()

add_executable(ArcherNOP
    ArcherNOP/exp.cpp
)

set_target_properties(ArcherNOP PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(ArcherNOP JuNOC++)

project(AutoDoorNOP VERSION 0.1.0)

add_executable(AutoDoorNOP
    AutoDoorNOP/exp.cpp
)

set_target_properties(AutoDoorNOP PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(AutoDoorNOP JuNOC++)

