project(my_project)
cmake_minimum_required(VERSION 3.24)
add_executable(vecmatrix) # also add_library(vecmatrix)
target_include_directories(vecmatrix
PUBLIC include/
PRIVATE src/)
# target_include_directories(vecadd SYSTEM ...) for system headers
target_sources(vecmatrix # best way for specifying
PRIVATE src/vecadd.cpp # program sources and headers
PRIVATE src/matrix.cpp
PUBLIC include/timecounters.h
PUBLIC include/matrix.h)
target_compile_definitions(vecmatrix PRIVATE TIMING)
target_compile_options(vecmatrix PRIVATE -g)
target_link_libraries(vecmatrix PRIVATE stdc++)
target_link_options(vecmatrix PRIVATE -s)

