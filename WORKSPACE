load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/v1.5.0.zip"],
    sha256 = "2d22dd3758afee43842bb504af1a8385cccb3ee1f164824e4837c1c1b04d92a0",
    strip_prefix = "benchmark-1.5.0",
)

http_archive(
    name = "abseil",
    urls = ["https://github.com/abseil/abseil-cpp/archive/20190808.zip"],
    sha256 = "0b62fc2d00c2b2bc3761a892a17ac3b8af3578bd28535d90b4c914b0a7460d4e",
    strip_prefix = "abseil-cpp-20190808",
)

# Gtest and its dependencies

http_archive(
    name = "rules_cc",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/master.zip"],
    sha256 = "9197b22ba3f10ed8eede900ca9a4a5bead8fa62d31ca266e4e4b63544ac5021e",
    strip_prefix = "rules_cc-master",
)

http_archive(
    name = "rules_python",
    urls = ["https://github.com/bazelbuild/rules_python/archive/master.zip"],
    sha256 = "46517092c83222d93553c06555ab4af72435000b3c58feb276161fc03f4ac5e5",
    strip_prefix = "rules_python-master",
)

http_archive(
    name = "gtest",
    urls = ["https://github.com/google/googletest/archive/release-1.10.0.zip"],
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    strip_prefix = "googletest-release-1.10.0",
)

# Glog and its deps

http_archive(
    name = "com_github_gflags_gflags",
    urls = [
        "https://mirror.bazel.build/github.com/gflags/gflags/archive/v2.2.2.tar.gz",
        "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
    ],
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2",
)

# Cannot use the release v0.4.0 because it does not print stack traces
# properly when built using bazel. The fix is not a part of the release
# https://github.com/google/glog/pull/347
http_archive(
    name = "glog",
    urls = ["https://github.com/google/glog/archive/6ca3d3cf5878020ebed7239139d6cd229a1e7edb.zip"],
    sha256 = "e94a39c4ac6fab6fdf75b37201e0333dce7fbd996e3f9c4337136ea2ecb634fc",
    strip_prefix = "glog-6ca3d3cf5878020ebed7239139d6cd229a1e7edb",
)
