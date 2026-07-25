cmake_minimum_required(VERSION 3.16)
project(Login)
add_executable(Login Code/main.cpp Code/console.cpp)
target_include_directories(Login PRIVATE Headers)