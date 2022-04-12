cmake_minimum_required(VERSION 3.16)

project(test_matrix)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_matrix test.cpp)

target_include_directories(test_matrix PUBLIC ./include PUBLIC ${Boost_INCLUDE_DIR})

set_target_properties(test_matrix PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(test_matrix PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(test_matrix
    ${Boost_LIBRARIES}
)
