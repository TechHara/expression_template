cmake_minimum_required(VERSION 3.0.0)
project(expression_template VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(naive naive.cc)
add_executable(lazy lazy.cc)
add_executable(expt expt.cc)