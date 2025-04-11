cmake_minimum_required(VERSION 3.30)
project(cli C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

add_executable(cli
        main.c
        actions.h
        build.c
        init.c
        run.c
)

find_path(ARGTABLE3_INCLUDE_DIR argtable3.h)
find_library(ARGTABLE3_LIBRARY argtable3)

target_include_directories(cli PRIVATE ${ARGTABLE3_INCLUDE_DIR})
target_link_libraries(cli PRIVATE ${ARGTABLE3_LIBRARY})

