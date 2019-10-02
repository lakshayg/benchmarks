cc_library(
    name = "counter",
    hdrs = ["counter.h"],
    deps = ["@abseil//absl/base:core_headers"], # absl/base/optimization.h
)

cc_binary(
    name = "false_sharing",
    srcs = ["false_sharing.cpp"],
    deps = [
        ":counter",
        "@google_benchmark//:benchmark",
        "@glog//:glog",
    ],
)
