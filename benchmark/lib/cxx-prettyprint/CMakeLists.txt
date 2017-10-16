cmake_minimum_required(VERSION 3.1)
project(cxx-prettyprint VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
endif()

add_library(cxx-prettyprint INTERFACE)

target_include_directories(
    cxx-prettyprint
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(cxx-prettyprint)

#set(HEADER_BASE "${CMAKE_CURRENT_SOURCE_DIR}/include")

#file(GLOB_RECURSE stringify_include_SRCS "${HEADER_BASE}/*.hpp")
#add_custom_target(stringify_headers_for_ide SOURCES ${stringify_include_SRCS})
