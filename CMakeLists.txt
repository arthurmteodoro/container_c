cmake_minimum_required(VERSION 3.13)
project(container_c C)

set(CMAKE_C_STANDARD 99)

add_executable(container_c src/include/utils.h src/utils.c src/include/stack.h src/stack.c test/test_stack.c)