cmake_minimum_required(VERSION 3.17)
project(LittleLanguage C)

set(CMAKE_C_STANDARD 99)

add_executable(LittleLanguage main.c lexer.c ll.h parser.c vm.c)

install(TARGETS LittleLanguage DESTINATION bin)