cmake_minimum_required(VERSION 3.14)
project(JuNOC++ VERSION 1.0.0 DESCRIPTION "JuNOC++: Just A Notification Oriented C++. A high level Notification Oriented Paradigm C++ framework")

option(JUNOCPP_TEST_ENABLE "Build JuNOC++ tests" ON)

file(GLOB JUNOCPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Utils/*.cpp
)

file(GLOB JUNOCPP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/Core/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/Utils/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/Utils/NOPTraits/*.hpp
)

set(JUNOCPP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/Utils/NOPTraits
)

add_library(JuNOC++ STATIC ${JUNOCPP_SOURCES} ${JUNOCPP_HEADERS})

set_target_properties(JuNOC++
    PROPERTIES CXX_STANDARD 20
)

target_include_directories(JuNOC++ PUBLIC ${JUNOCPP_INCLUDE_DIRS})

install(TARGETS JuNOC++
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}     
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

export(TARGETS JuNOC++ FILE ${CMAKE_CURRENT_BINARY_DIR}/JuNOC++.cmake)

export(PACKAGE JuNOCpp)

if(JUNOCPP_TEST_ENABLE)
    add_subdirectory(tests)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/JuNOCpp.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/JuNOCpp.cmake @ONLY
)