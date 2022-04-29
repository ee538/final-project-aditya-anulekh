load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "TravellingTrojan_benchmark",
    srcs = ["TravellingTrojan_benchmark.cc"],
    deps = [
        "@com_google_benchmark//:benchmark",
        "//src/lib:TrojanMap",
    ],
)

cc_binary(
    name = "AutoComplete_benchmark",
    srcs = ["AutoComplete_benchmark.cc"],
    deps = [
        "@com_google_benchmark//:benchmark",
        "//src/lib:TrojanMap",
    ],
)

cc_binary(
    name = "FindNearby_benchmark",
    srcs = ["FindNearby_benchmark.cc"],
    deps = [
        "@com_google_benchmark//:benchmark",
        "//src/lib:TrojanMap",
    ],
)