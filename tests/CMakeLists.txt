cmake_minimum_required(VERSION 3.14)

################################
# Unit Tests
################################
add_executable(junocpp_test tests.cpp tests-main.cpp)

set_target_properties(junocpp_test PROPERTIES
	CXX_STANDARD 20
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wa,-mbig-obj")

target_link_libraries(junocpp_test JuNOC++)

add_test(NAME junocpp_test
		COMMAND junocpp_test)