cmake_minimum_required(VERSION 3.30)
include(fetchcontent)
project(parser_tests CXX)


add_executable(parser_tests
        test_main.cpp)


### ==== [ vcpkg ] ====
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")


### ==== [ parser ] ====
set(PARSER_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../src/parser")
FetchContent_Declare(
        parser
        SOURCE_DIR ${PARSER_PROJECT_DIR}
)

FetchContent_MakeAvailable(parser)


target_link_libraries(parser_tests PUBLIC parser)
target_include_directories(parser_tests PUBLIC ${PARSER_PROJECT_DIR})


### ==== [ gtest ] ====
find_package(GTest CONFIG REQUIRED)
target_link_libraries(parser_tests PRIVATE GTest::gtest GTest::gtest_main)