cmake_minimum_required(VERSION 3.20)

project(qdecimal VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Core5Compat Test)
qt_standard_project_setup()

add_subdirectory(decnumber)
add_subdirectory(src)

enable_testing() 
add_subdirectory(test)
