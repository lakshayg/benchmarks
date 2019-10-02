#pragma once

#include "absl/base/optimization.h"

namespace lg {

// NormalCounters is straight forward naive implementation of a struct of
// counters.
// Note: We also use ABSL_CACHELINE_ALIGNED on the NormalCounters struct, but
// not its members, so that the entire struct will be aligned to a cache line.
// Otherwise the struct might be placed towards the end of a cache line,
// accidentally straddling two cache lines, thereby improving its performance.
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

// CacheLineAwareCounters forces each counter onto a separate cache line to
// avoid any false sharing between the counters.
// Note: We must use ABSL_CACHELINE_ALIGNED for each member, since we want to
// pad every single counter so it will be forced onto its own separate cache
// line.
template <typename CounterT, size_t N>
class ABSL_CACHELINE_ALIGNED CacheLineAwareCounter {
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
  struct ABSL_CACHELINE_ALIGNED AlignedCounter {
    CounterT counter{0};
  };

  AlignedCounter counters[N] = {};
};
} // namespace lg

// static_assert(
//     sizeof(NormalCounters) != sizeof(CacheLineAwareCounters),
//     "NormalCounters and CacheLineAwareCounters should have different sizes due "
//     "to aligning members to different cache lines -- otherwise benchmarks will "
//     "not show the difference in performance.");
