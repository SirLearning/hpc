project(my_project
LANGUAGES CXX)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
add_executable(vecadd ${PROJECT_SOURCE_DIR}/vecadd.cpp) 
# PROJECT_SOURCE_DIR is the root directory of the project
