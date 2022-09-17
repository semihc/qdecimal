cmake_minimum_required(VERSION 3.16)

project(qdecimal VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Core5Compat Test)

#qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
cmake_policy(SET CMP0100 NEW)

add_subdirectory(decnumber)
add_subdirectory(src)

enable_testing() 
add_subdirectory(test)
