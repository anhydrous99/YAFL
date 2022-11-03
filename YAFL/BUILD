package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "YAFL",
    srcs = ["base.cc",
            "base.h",
            "utils.h",
           ],
    hdrs = [
        "base.h",
        "utils.h"
        ],
    copts = ['-std=c++17'],
    deps = ["@cfitsio//:cfitsio"]
)
