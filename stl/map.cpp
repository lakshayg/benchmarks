#include "absl/base/optimization.h"
#include "benchmark/benchmark.h"
#include <map>

struct Foo {
  std::vector<int> vector;
  int a, b, c, d;
};

constexpr int kNumInterations = 1 << 16;

std::string makeKey(int len) {
  std::string s = "";
  while (len-- > 0) {
    s += "k";
  }
  return s;
}

template <typename T>
T& findOrEmplace(std::map<std::string, T>& map, const std::string& key) {
  auto it = map.find(key);
  if (ABSL_PREDICT_TRUE(it != map.end())) {
    return it->second;
  }
  const auto& pair = map.emplace(key, Foo());
  return pair.first->second;
}

template <typename T>
T& emplace(std::map<std::string, T>& map, const std::string& key) {
  const auto& pair = map.emplace(key, Foo());
  return pair.first->second;
}

static void BM_FindOrEmplace(benchmark::State& state) {
  const std::string key = makeKey(state.range(0));
  for (auto _ : state) {
    std::map<std::string, Foo> map;
    for (int i = 0; i < kNumInterations; ++i) {
      auto& obj = findOrEmplace(map, key);
      benchmark::DoNotOptimize(obj);
    }
  }
}
BENCHMARK(BM_FindOrEmplace)
  ->Arg(2)
  ->Arg(4)
  ->Arg(8)
  ->Arg(16)
  ->Arg(32)
  ->Arg(64)
  ->Arg(128)
  ->Unit(benchmark::kMicrosecond);

static void BM_Emplace(benchmark::State& state) {
  const std::string key = makeKey(state.range(0));
  for (auto _ : state) {
    std::map<std::string, Foo> map;
    for (int i = 0; i < kNumInterations; ++i) {
      auto& obj = emplace(map, key);
      benchmark::DoNotOptimize(obj);
    }
  }
}
BENCHMARK(BM_Emplace)
  ->Arg(2)
  ->Arg(4)
  ->Arg(8)
  ->Arg(16)
  ->Arg(32)
  ->Arg(64)
  ->Arg(128)
  ->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
