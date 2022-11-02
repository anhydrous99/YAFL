load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "test",
    srcs = ["test.cc"],
    deps = [
        "//YAFL:YAFL",
        "@com_google_googletest//:gtest_main"
    ]
)