find_package(Threads REQUIRED)

add_library(stringify::stringify ALIAS stringify)
add_library(cxx-prettyprint::cxx-prettyprint ALIAS cxx-prettyprint)
add_library(benchmark::benchmark ALIAS benchmark)

add_executable(vector_benchmark vector_benchmark.cpp)
target_link_libraries(vector_benchmark
	benchmark::benchmark
	stringify::stringify
	cxx-prettyprint::cxx-prettyprint
)

add_executable(map_benchmark map_benchmark.cpp)
target_link_libraries(map_benchmark
	benchmark::benchmark
	stringify::stringify
	cxx-prettyprint::cxx-prettyprint
)
