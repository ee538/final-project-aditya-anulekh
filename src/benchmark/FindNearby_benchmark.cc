#include "benchmark/benchmark.h"

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <string_view>
#include <vector>
#include "src/lib/trojanmap.h"

TrojanMap trojanmap;

static void BM_FindNearby(benchmark::State& state) {
  for (auto _ : state) {
    trojanmap.FindNearby("cafe", "Ralphs", state.range(0), 10);
  }
}

// Register the function as a benchmark

// Benchmark find nearby function
BENCHMARK(BM_FindNearby)->DenseRange(0, 100, 4);

// Run the benchmark
BENCHMARK_MAIN();