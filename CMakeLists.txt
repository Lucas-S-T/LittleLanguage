cmake_minimum_required(VERSION 3.17)
project(LittleLanguage C)

set(CMAKE_C_STANDARD 99)

add_executable(LittleLanguage main.c lexer.c ll.h parser.c vm.c instructions/memory.c instructions/output.c instructions/functions.c instructions/stack.c instructions/variables.c instructions/arithmetic.c instructions/jump.c)

install(TARGETS LittleLanguage DESTINATION bin)