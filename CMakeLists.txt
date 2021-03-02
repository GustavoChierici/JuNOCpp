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


project(ColisionNOP VERSION 0.1.0)

file(GLOB SRC
	${CMAKE_CURRENT_SOURCE_DIR}/ColisionNOP/src/*.cpp	
)

file(GLOB INC
	${CMAKE_CURRENT_SOURCE_DIR}/ColisionNOP/include/*.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ColisionNOP/include/)

add_executable(ColisionNOP
	${SRC}
	${INC}
)

set_target_properties(ColisionNOP PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(ColisionNOP JuNOC++)

project(NOPBitonic VERSION 0.1.0)

file(GLOB SRC
	${CMAKE_CURRENT_SOURCE_DIR}/NOPBitonic/src/*.cpp	
)

file(GLOB INC
	${CMAKE_CURRENT_SOURCE_DIR}/NOPBitonic/include/*.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/NOPBitonic/include/)

add_executable(NOPBitonic
	${SRC}
	${INC}
)

set_target_properties(NOPBitonic PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(NOPBitonic JuNOC++)

project(NOPSensors VERSION 0.1.0)

include(FetchContent)
FetchContent_Declare(libnop
    GIT_REPOSITORY http://nop.dainf.ct.utfpr.edu.br/NOP-Server/NOP-Frameworks/Cpp-Framework-4_0.git
    GIT_TAG master
)

set(LIBNOP_TEST_ENABLE OFF)

FetchContent_GetProperties(libnop)
if(NOT libnop_POPULATED)
    FetchContent_MakeAvailable(libnop)
endif()


file(GLOB SRC
	${CMAKE_CURRENT_SOURCE_DIR}/NOPSensors/src/*.cpp	
)

file(GLOB INC
	${CMAKE_CURRENT_SOURCE_DIR}/NOPSensors/include/*.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/NOPSensors/include/)

add_executable(NOPSensors
	${SRC}
	${INC}
)

set_target_properties(NOPSensors PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(NOPSensors JuNOC++)

project(NOPSensorsFW4 VERSION 0.1.0)


file(GLOB SRC
	${CMAKE_CURRENT_SOURCE_DIR}/NOPSensorsFW4/*.cpp	
)

file(GLOB INC
	${CMAKE_CURRENT_SOURCE_DIR}/NOPSensorsFW4/*.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/NOPSensorsFW4/)

add_executable(NOPSensorsFW4
	${SRC}
	${INC}
)

set_target_properties(NOPSensorsFW4 PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(NOPSensorsFW4 libnop)


