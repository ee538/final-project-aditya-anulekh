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

// Register the function as a benchmark

// Benchmark autocomplete function 
BENCHMARK(BM_AutoComplete)->DenseRange(1, 100, 10);

// Run the benchmark
BENCHMARK_MAIN();