load("//third_party/zlib:direct.bzl", "load_zlib")
load("//third_party/cfitsio:direct.bzl", "load_cfitsio")
load("//third_party/googletest:direct.bzl", "load_googletest")

def load_third_party_libraries():
    load_zlib()
    load_cfitsio()
    load_googletest()
    