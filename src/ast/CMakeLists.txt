cmake_minimum_required(VERSION 3.30)
project(ast C)

add_library(ast STATIC
        tokens.c
        tokens.h
        ast.c
        ast.h)