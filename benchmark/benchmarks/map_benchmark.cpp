#include <benchmark/benchmark.h>
#include <stringify/stringify.hpp>
#include <prettyprint.hpp>
#include <map>
#include <sstream>

static void BM_IntMapStringifyPrint(benchmark::State& state)
{
	std::map<int, int> mp;
	for(auto i = 0; i < 10; i++)
	{
		mp[i] = i;
	}
	std::stringstream ss;

  	while (state.KeepRunning())
  	{
    	ss << stringify::to_string(mp); 
  	}
}
BENCHMARK(BM_IntMapStringifyPrint);

static void BM_IntMapCxxPrettyPrint(benchmark::State& state)
{
	std::map<int, int> mp;
	for(auto i = 0; i < 10; i++)
	{
		mp[i] = i;
	}
	std::stringstream ss;

  	while (state.KeepRunning())
  	{
    	ss << mp; 
  	}
}
BENCHMARK(BM_IntMapCxxPrettyPrint);

BENCHMARK_MAIN()
