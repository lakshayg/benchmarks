cc_library(
    name = "ctype",
    hdrs = ["ctype.h"],
    srcs = ["src/ctype.cpp"],
)

cc_library(
    name = "stdlib",
    hdrs = ["stdlib.h"],
    srcs = ["src/atoi.cpp"],
    deps = [":ctype"],
)

cc_library(
    name = "string",
    hdrs = ["string.h"],
)

cc_test(
    name = "atoi_test",
    srcs = ["test/atoi_test.cpp"],
    deps = [
        ":stdlib",
        "@gtest//:gtest",
        "@gtest//:gtest_main",
    ],
)
