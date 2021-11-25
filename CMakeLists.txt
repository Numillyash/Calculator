cmake_minimum_required(VERSION 3.20)
project(LCalc C)

#set(CMAKE_C_STANDARD 11)

add_executable(LCalc main.c stack.h stack_signs.h structure.h structure.c)
add_executable(Test test.c stack.h stack_signs.h structure.h structure.c)
