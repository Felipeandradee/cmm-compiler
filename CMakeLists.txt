cmake_minimum_required(VERSION 3.8)
project(cmm_compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        lexico.c
        lexico.h
        main.c
        sintatico.c
        sintatico.h)

add_executable(cmm_compiler ${SOURCE_FILES})