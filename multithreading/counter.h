#pragma once

#include "absl/base/optimization.h"

namespace lg {

// SimpleCounter is naive implementation of a struct of counters.
// Note: We use ABSL_CACHELINE_ALIGNED on the SimpleCounter struct, but
// not its members, so that the entire struct will be aligned to a cache
// line. Otherwise the struct might be placed towards the end of a cache
// line, accidentally straddling two cache lines, thereby improving its
// performance.
template <typename CounterT, size_t N>
class ABSL_CACHELINE_ALIGNED SimpleCounter {
 public:
  static constexpr size_t num_counters = N;

  template <typename T>
  void set(size_t n, const T& value) {
    counters[n] = value;
  }

  void inc(size_t n) {
    ++counters[n];
  }

  const CounterT& get(size_t n) const {
    return counters[n];
  }

 private:
  CounterT counters[N] = {};
};

// CacheLineAwareCounter forces each counter onto a separate
// cache line to avoid any false sharing between the counters
template <typename CounterT, size_t N>
class CacheLineAwareCounter {
 public:
  static constexpr size_t num_counters = N;

  template <typename T>
  void set(size_t n, const T& value) {
    counters[n].counter = value;
  }

  void inc(size_t n) {
    ++counters[n].counter;
  }

  const CounterT& get(size_t n) const {
    return counters[n].counter;
  }

 private:
  // All instances of AlignedCounter will be aligned to the cache line
  struct ABSL_CACHELINE_ALIGNED AlignedCounter {
    CounterT counter{ 0 };
  };

  AlignedCounter counters[N] = {};
};
} // namespace lg
