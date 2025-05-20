
project(my_project) # project name
add_executable(vecadd vecadd.cpp) # compile command

if (VAR)
message("VAR is set, NUM is ${NUM}")
else()
message(FATAL_ERROR "VAR is not set")
endif()
