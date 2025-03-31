cmake_minimum_required(VERSION 3.30)
project(lisp_llvm C)


add_executable(lisp_llvm main.c)


### ==== [ argtable3 ] ====
find_path(ARGTABLE3_INCLUDE_DIR argtable3.h)
find_library(ARGTABLE3_LIBRARY argtable3)

target_include_directories(lisp_llvm PRIVATE ${ARGTABLE3_INCLUDE_DIR})
target_link_libraries(lisp_llvm PRIVATE ${ARGTABLE3_LIBRARY})


### ==== [ LLVM ] ====
find_package(LLVM REQUIRED CONFIG)

target_include_directories(lisp_llvm PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(lisp_llvm PRIVATE ${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs
        core
        interpreter
        executionengine
        target
        asmprinter
        native
        nativecodegen
        support
)

target_link_libraries(lisp_llvm PRIVATE ${llvm_libs})
