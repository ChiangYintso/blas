// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

#include <benchmark/benchmark.h>
#include <eigen3/Eigen/Dense>
#include <iostream>

static void add_scalar(auto &arr) {
  for (int i = 0; i < 10000; ++i) {
    arr += (float) i;
  }
}

static void BM_AddScalar(benchmark::State &state) {
  // Perform setup here
  Eigen::Matrix<float, 100, 100> m;
  auto arr = m.array();
  for (auto _ : state) {
    // This code gets timed
    add_scalar(arr);
  }
  std::cout << m.coeffRef(0, 0) << std::endl;
}
// Register the function as a benchmark
BENCHMARK(BM_AddScalar);
// Run the benchmark
BENCHMARK_MAIN();
