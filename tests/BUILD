load("@rules_cc//cc:defs.bzl", "cc_test")

filegroup(
    name = "test-data",
    srcs = [
        "test-data/acisfJ0000082p135624_001N026_mrgsrc3.fits",
        "test-data/acisfJ0013281p405149_001N021_b_img3.fits"
    ]
)

cc_test(
    name = "test",
    srcs = ["test.cc"],
    deps = [
        "//YAFL:YAFL",
        "@com_google_googletest//:gtest_main"
    ],
    data = ["//tests:test-data"]
)
