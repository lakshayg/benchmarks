// Reference:
// * https://paulcavallaro.com/blog/common-systems-programming-optimizations-tricks/
// * https://igoro.com/archive/gallery-of-processor-cache-effects/

#include "benchmark/benchmark.h"
#include "glog/logging.h"
#include <iostream>

#include "base/init.h"
#include "counter.h"

constexpr int64_t kNumIncrements = int64_t{1} << 16;

template <typename Counters>
void IncrementCounters(benchmark::State& state) {
  // Setup for benchmark
  static Counters counters; // static so all threads use the same counter
  const int thread_idx = state.thread_index;
  CHECK_LT(thread_idx, Counters::num_counters);
  counters.set(thread_idx, 0);

  // Benchmark
  for (auto _ : state) {
    for (int64_t i = 0; i < kNumIncrements; ++i) {
      counters.inc(thread_idx);
      benchmark::ClobberMemory();
    }
  }

  // Ensure that the benchmark did what we expected
  auto expected_count = state.iterations()  * kNumIncrements;
  CHECK_EQ(counters.get(thread_idx), expected_count);
}

#define REGISTER_BENCHMARK_FOR(CounterType)                   \
  BENCHMARK_TEMPLATE(IncrementCounters, CounterType)          \
    ->Threads(1)                                              \
    ->Threads(2)                                              \
    ->Threads(3)                                              \
    ->Threads(4)                                              \
    ->Threads(5)                                              \
    ->Threads(6)                                              \
    ->Threads(7)                                              \
    ->Threads(8)                                              \
    ->Unit(benchmark::kMicrosecond)

constexpr int kMaxThreads = 8;

using SimpleCounter_Int = lg::SimpleCounter<size_t, kMaxThreads>;
REGISTER_BENCHMARK_FOR(SimpleCounter_Int);

using CacheLineAwareCounter_Int = lg::CacheLineAwareCounter<size_t, kMaxThreads>;
REGISTER_BENCHMARK_FOR(CacheLineAwareCounter_Int);

using SimpleCounter_AtomicInt = lg::SimpleCounter<std::atomic_int, kMaxThreads>;
REGISTER_BENCHMARK_FOR(SimpleCounter_AtomicInt);

using CacheLineAwareCounter_AtomicInt = lg::CacheLineAwareCounter<std::atomic_int, kMaxThreads>;
REGISTER_BENCHMARK_FOR(CacheLineAwareCounter_AtomicInt);

int main(int argc, char** argv) {
  LG_INIT_GLOG(argc, argv);

  LOG(INFO) << "Cache line size: " << ABSL_CACHELINE_SIZE;
  LOG(INFO) << "sizeof(SimpleCounter_Int) = " << sizeof(SimpleCounter_Int);
  LOG(INFO) << "sizeof(CacheLineAwareCounter_Int) = " << sizeof(CacheLineAwareCounter_Int);
  LOG(INFO) << "sizeof(SimpleCounter_AtomicInt) = " << sizeof(SimpleCounter_AtomicInt);
  LOG(INFO) << "sizeof(CacheLineAwareCounter_AtomicInt) = " << sizeof(CacheLineAwareCounter_AtomicInt);

  benchmark::Initialize(&argc, argv);
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) {
    return 1;
  }
  benchmark::RunSpecifiedBenchmarks();
}
