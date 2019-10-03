#include "benchmark/benchmark.h"
#include "glog/logging.h"

// Functions to test

void transpose_simple(double* a, int n_rows, int n_cols) {
  for (int i = 0; i < n_rows; ++i) {
    for (int j = i + 1; j < n_cols; ++j) {
      std::swap(a[i * n_cols + j], a[j * n_cols + i]);
    }
  }
}

// Test

template <typename Function>
void test(Function transpose_func) {
  double a[3][3];
  a[0][0] = 1;
  a[0][1] = 2;
  a[0][2] = 3;
  a[1][0] = 4;
  a[1][1] = 5;
  a[1][2] = 6;
  a[2][0] = 7;
  a[2][1] = 8;
  a[2][2] = 9;

  transpose_func(&a[0][0], 3, 3);

  CHECK_EQ(a[0][0], 1);
  CHECK_EQ(a[0][1], 4);
  CHECK_EQ(a[0][2], 7);
  CHECK_EQ(a[1][0], 2);
  CHECK_EQ(a[1][1], 5);
  CHECK_EQ(a[1][2], 8);
  CHECK_EQ(a[2][0], 3);
  CHECK_EQ(a[2][1], 6);
  CHECK_EQ(a[2][2], 9);
}

std::unique_ptr<double[]> matrix(int rows, int cols) {
  std::unique_ptr<double[]> data(new double[rows * cols]);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int pos = i * cols + j;
      data[pos] = pos;
    }
  }
  return data;
}

// Benchmarks

static void BM_TransposeSimple(benchmark::State& state) {
  int size = state.range(0);
  auto data = matrix(size, size);
  for (auto _ : state) {
    transpose_simple(data.get(), size, size);
    benchmark::DoNotOptimize(data);
  }
  state.SetBytesProcessed(state.iterations() * size * size * sizeof(double));
}

BENCHMARK(BM_TransposeSimple) // Results
  ->Arg(63)                   //  1.09 us     items_per_second=3.66534G/s
  ->Arg(64)                   //  1.22 us     items_per_second=3.4029G/s
  ->Arg(65)                   //  1.21 us     items_per_second=3.52546G/s
  ->Arg(127)                  //  4.47 us     items_per_second=3.62383G/s
  ->Arg(128)                  //  32.8 us     items_per_second=501.395M/s   ????
  ->Arg(129)                  //  4.80 us     items_per_second=3.48054G/s
  ->Arg(511)                  //   177 us     items_per_second=1.48156G/s
  ->Arg(512)                  //  1197 us     items_per_second=220.024M/s   ????
  ->Arg(513)                  //   298 us     items_per_second=886.698M/s
  ->Unit(benchmark::kMicrosecond);

/*
 * The weird result above can be understood by considering how CPU caches work.
 * Caches are typically organized into lines and sets. For example, consider a
 * 8kB cache.with line size of 64 bytes. Such a cache will have (8 * 1024) / 64
 * = 128 cache lines in total. These are organized into 32 sets with 4 lines per
 * set. Visualize this as follows
 *
 * 0          64        128        192
 * 2048       ...
 *   ########   ########   ########   ....
 *   ########   ########   ########   ....
 *   ########   ########   ########   ....
 *   ########   ########   ########   ....
 *    Set 1      Set 2      Set 3
 *
 * 0-64 bytes map to set 1, 64-128 map to set 2 and so on. Once we reach the
 * last set, we cycle back to 1. Within a set, cache line is selected based on a
 * policy like Least Recently Used (LRU), Not Most Recently Used (NMRU) etc.
 *
 * If we access memory addresses separated by (cache line size * number of sets)
 * bytes, then both the memory locations will be mapped to the same cache set.
 * In the transpose example, when the matrix size is a multiple of this critical
 * size, we end up hitting only a small number of cache sets rather than
 * utilizing the entire cache thus causing contention for cache and reducing
 * performance severely
 */

int main(int argc, char** argv) {
  google::InstallFailureSignalHandler();
  google::InitGoogleLogging(argv[0]);

  test(transpose_simple);

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
