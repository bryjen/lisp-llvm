cmake_minimum_required(VERSION 3.30)
include(fetchcontent)
project(parser C)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /RTC1" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG" CACHE STRING "" FORCE)

set(AST_PROJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ast")
FetchContent_Declare(
        ast
        SOURCE_DIR ${AST_PROJ_DIR}
)

FetchContent_MakeAvailable(ast)


add_library(parser STATIC
        tokenizer.h tokenizer.c
        parser.h parser.c)

target_link_libraries(parser PUBLIC ast)
target_include_directories(parser PUBLIC ${AST_PROJ_DIR})
