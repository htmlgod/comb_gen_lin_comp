cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# hunter module, keep up-to-date
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.24.14.tar.gz"
    SHA1 "00901c19eefc02d24b16705b5f5a2b4f093a73fb"
)

project(comb_gen_lin_comp)
option(BUILD_TESTS "Build tests" ON)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

add_library(
    ${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    ${PROJECT_NAME}
    Boost::boost
)

include(cmake/packaging.cmake)
if(BUILD_TESTS)
    enable_testing()
    add_executable("${PROJECT_NAME}_tests"
        tests/tests.cpp
    )
    target_link_libraries(
      "${PROJECT_NAME}_tests"
      GTest::gtest_main
      ${PROJECT_NAME}
    )
    include(GoogleTest)
    gtest_discover_tests("${PROJECT_NAME}_tests")
endif()
