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

std::string GenerateRandomString(std::size_t n) {
  static constexpr auto chars =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";

  auto result = std::string(n, '\0');
  std::generate_n(std::begin(result), n,
                  [&]() { return chars[rand() % std::strlen(chars)]; });
  return result;
}

static void BM_AutoComplete(benchmark::State& state) {
  std::string s = GenerateRandomString(state.range(0));
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    trojanmap.Autocomplete(s);
  }
}

static void BM_TravellingTrojan_Brute_force(benchmark::State& state) {
  std::vector<std::string> keys;
  for (auto x : trojanmap.data) {
    keys.push_back(x.first);
  }
  std::vector<std::string> locations;
  srand(time(NULL));
  for (int i = 0; i < state.range(0); i++)
    locations.push_back(keys[rand() % keys.size()]);
  
  for (auto _ : state) {
    trojanmap.TravellingTrojan_Brute_force(locations);
  }
}

static void BM_TravellingTrojan_Backtracking(benchmark::State& state) {
  std::vector<std::string> keys;
  for (auto x : trojanmap.data) {
    keys.push_back(x.first);
  }
  std::vector<std::string> locations;
  srand(time(NULL));
  for (int i = 0; i < state.range(0); i++)
    locations.push_back(keys[rand() % keys.size()]);
  
  for (auto _ : state) {
    trojanmap.TravellingTrojan_Backtracking(locations);
  }
}


static void BM_TravellingTrojan_2opt(benchmark::State& state) {
  std::vector<std::string> keys;
  for (auto x : trojanmap.data) {
    keys.push_back(x.first);
  }
  std::vector<std::string> locations;
  srand(time(NULL));
  for (int i = 0; i < state.range(0); i++)
    locations.push_back(keys[rand() % keys.size()]);
  
  for (auto _ : state) {
    trojanmap.TravellingTrojan_2opt(locations);
  }
}

// Register the function as a benchmark

// Benchmark autocomplete function 
// BENCHMARK(BM_AutoComplete)->RangeMultiplier(2)->Range(1 << 10, 1 << 20);

// Benchmark travelling trojan brute force function
BENCHMARK(BM_TravellingTrojan_Brute_force)->DenseRange(2, 10, 1);
BENCHMARK(BM_TravellingTrojan_Backtracking)->DenseRange(2, 13, 1);
BENCHMARK(BM_TravellingTrojan_2opt)->DenseRange(2, 16, 1);


// Run the benchmark
BENCHMARK_MAIN();