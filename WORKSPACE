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

http_archive(
    name = "glog",
    urls = ["https://github.com/google/glog/archive/v0.4.0.zip"],
    strip_prefix = "glog-0.4.0",
)
