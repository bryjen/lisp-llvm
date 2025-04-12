cmake_minimum_required(VERSION 3.30)
include(fetchcontent)
project(parser C)

set(AST_PROJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ast")
FetchContent_Declare(
        ast
        SOURCE_DIR ${AST_PROJ_DIR}
)

message(STATUS "${AST_PROJ_DIR}")

FetchContent_MakeAvailable(ast)


add_library(parser STATIC
        tokenizer.h tokenizer.c
        parser.h parser.c)

target_link_libraries(parser PUBLIC ast)
target_include_directories(parser PUBLIC ${AST_PROJ_DIR})
