// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

#include <benchmark/benchmark.h>
#include <libra/matrix.h>
#include <iostream>

static void add_scalar(auto &m) {
  for (int i = 0; i < 10000; ++i) {
    m += (float) i;
  }
}

static void BM_AddScalar(benchmark::State &state) {
  // Perform setup here
  libra::Matrix<float, 100, 100> m{};
  for (auto _ : state) {
    // This code gets timed
    add_scalar(m);
  }
  std::cout << m[0][0] << std::endl;
}

// Register the function as a benchmark
BENCHMARK(BM_AddScalar);
// Run the benchmark
BENCHMARK_MAIN();
