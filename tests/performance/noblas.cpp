#include "blocked.h"
#include "common.h"
#include "naive.h"

#include <benchmark/benchmark.h>

static void benchmark_solver(benchmark::State &state, const Solver &solve) {
  size_t n = state.range(0);
  auto L = create_random_L(n);
  auto b = create_random_b(n);

  for (auto _ : state) {
    solve(L, b);
  }

  state.counters["flops"] = benchmark::Counter(
      static_cast<double>(state.iterations() * n * (n - 1)),
      benchmark::Counter::kIsRate,
      benchmark::Counter::kIs1000);
}

BENCHMARK_CAPTURE(benchmark_solver, naive, solvers::naive)
    ->DenseRange(32, 1024, 32)
    ->DenseRange(1536, 4096, 512)
    ->ReportAggregatesOnly();

BENCHMARK_CAPTURE(benchmark_solver, blocked, solvers::blocked)
    ->DenseRange(32, 1024, 32)
    ->DenseRange(1536, 4096, 512)
    ->ReportAggregatesOnly();

BENCHMARK_MAIN();
