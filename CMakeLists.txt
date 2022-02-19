cmake_minimum_required(VERSION 3.20)
project(HomeWork5)

set(CMAKE_CXX_STANDARD 14)

add_library(Matrix SHARED matrix.cpp matrix.h)
add_executable(Matrix.Test main.cpp Tests.cpp)
target_link_libraries(Matrix.Test Matrix gtest pthread)
