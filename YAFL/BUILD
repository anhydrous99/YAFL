package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "hello-world",
    srcs = ["hello-world.cc",
            "hello-world.h"
           ],
    hdrs = ["hello-world.h"],
    deps = ["@cfitsio//:cfitsio"]
)
