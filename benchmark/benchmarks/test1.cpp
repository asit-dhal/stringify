//#include <iostream>
//#include <vector>

//#include "prettyprint.hpp"

//int main()
//{
//    std::vector<int> v;
//    for(int i=0; i < 10; i++)
//    {
//        v.push_back(i*10);
//    }

//    std::cout<<"vector: " << v << std::endl;
//    return 0;
//}

#include <benchmark/benchmark.h>

static void BM_StringCreation(benchmark::State& state) {
  while (state.KeepRunning())
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  while (state.KeepRunning())
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN()
