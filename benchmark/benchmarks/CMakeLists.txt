find_package(Threads REQUIRED)

add_library(stringify::stringify ALIAS stringify)
add_library(cxx-prettyprint::cxx-prettyprint ALIAS cxx-prettyprint)
add_library(benchmarklib::benchmarklib ALIAS benchmarklib)

message("flags ${CMAKE_EXE_LINKER_FLAGS}")

add_executable(test1 test1.cpp)

target_link_libraries(test1 cxx-prettyprint::cxx-prettyprint)
target_link_libraries(test1 benchmarklib::benchmarklib)

