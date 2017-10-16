#include <benchmark/benchmark.h>
#include <stringify/stringify.hpp>
#include <prettyprint.hpp>
#include <vector>
#include <sstream>

static void BM_IntVectorStringifyPrint(benchmark::State& state)
{
	std::vector<int> vec;
	for(auto i = 0; i < 10; i++)
	{
		vec.emplace_back(i);
	}
	std::stringstream ss;

  	while (state.KeepRunning())
  	{
    	ss << stringify::to_string(vec); 
  	}
}
// Register the function as a benchmark
BENCHMARK(BM_IntVectorStringifyPrint);

static void BM_IntVectorPrettyPrint(benchmark::State& state)
{
	std::vector<int> vec;
	for(auto i = 0; i < 10; i++)
	{
		vec.emplace_back(i);
	}
	std::stringstream ss;

  	while (state.KeepRunning())
  	{
    	ss << vec; 
  	}
}
BENCHMARK(BM_IntVectorPrettyPrint);

BENCHMARK_MAIN()
