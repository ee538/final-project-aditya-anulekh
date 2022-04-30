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

static void BM_TravellingTrojan_distances(benchmark::State& state) {
  std::vector<std::string> keys;
  for (auto x : trojanmap.data) {
    keys.push_back(x.first);
  }
  std::vector<std::string> locations;
  srand(time(NULL));
  for (int i = 0; i < state.range(0); i++)
    locations.push_back(keys[rand() % keys.size()]);
  std::pair<double, std::vector<std::vector<std::string>>> results_brute_force;  
  std::pair<double, std::vector<std::vector<std::string>>> results_backtracking;  
  std::pair<double, std::vector<std::vector<std::string>>> results_2opt;  
  for (auto _ : state) {
    results_brute_force = trojanmap.TravellingTrojan_Brute_force(locations);
    results_backtracking = trojanmap.TravellingTrojan_Backtracking(locations);
    results_2opt = trojanmap.TravellingTrojan_2opt(locations);
  }
  state.counters["distance_bf"] = results_brute_force.first;
  state.counters["distance_bt"] = results_backtracking.first;
  state.counters["distance_2opt"] = results_2opt.first;
}


// Register the function as a benchmark

BENCHMARK(BM_TravellingTrojan_distances)->DenseRange(2, 10, 1)->Iterations(1);


// Run the benchmark
BENCHMARK_MAIN();