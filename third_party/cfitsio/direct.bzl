load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def load_cfitsio():
    maybe(
        http_archive,
        name = "cfitsio",
        url = "http://heasarc.gsfc.nasa.gov/FTP/software/fitsio/c/cfitsio-4.1.0.tar.gz",
        sha256 = "b367c695d2831958e7166921c3b356d5dfa51b1ecee505b97416ba39d1b6c17a",
        strip_prefix = "cfitsio-4.1.0",
        build_file = "//third_party/cfitsio:BUILD",
    )