cmake_minimum_required(VERSION 3.0)
project(stringifyBenchmarks)

set(CMAKE_CXX_STANDARD 11)

if(TARGET stringify)
  # Part of the main project
  add_library(stringify::stringify ALIAS stringify)
else()
  # Stand-alone build
  find_package(stringify CONFIG REQUIRED)
endif()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

