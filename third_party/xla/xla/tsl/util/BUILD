# Description:
#   Tensor Standard Libraries - common utilities for implementing XLA.
#
#   The libraries in this package are not allowed to have ANY dependencies
#   to other TF components outside of TSL.

load(
    "//xla/tsl:tsl.bzl",
    "check_deps",
    "internal_visibility",
    "tsl_copts",
)
load("//xla/tsl:tsl.default.bzl", "filegroup", "get_compatible_with_portable")
load(
    "//xla/tsl/platform:build_config.bzl",
    "tsl_cc_test",
)
load(
    "//xla/tsl/platform:build_config_root.bzl",
    "if_static",
)
load(
    "//xla/tsl/platform:rules_cc.bzl",
    "cc_library",
)

package(
    # copybara:uncomment default_applicable_licenses = ["//tensorflow:license"],
    default_visibility = [
        "//visibility:public",
    ],
    licenses = ["notice"],
)

filegroup(
    name = "mobile_srcs_no_runtime",
    srcs = [
        "byte_swap_array.cc",
        "byte_swap_array.h",
    ],
)

filegroup(
    name = "mobile_srcs_only_runtime",
    srcs = [
        "command_line_flags.cc",
        "command_line_flags.h",
        "determinism.cc",
        "determinism.h",
        "device_name_utils.cc",
        "device_name_utils.h",
        "env_var.cc",
        "env_var.h",
        "use_cudnn.cc",
        "use_cudnn.h",
    ],
)

filegroup(
    name = "determnism_hdr",
    srcs = [
        "determinism.h",
    ],
    compatible_with = get_compatible_with_portable(),
    visibility = internal_visibility([
        "//tensorflow:__subpackages__",
        "//tensorflow/core/util:__pkg__",
    ]),
)

filegroup(
    name = "framework_internal_private_hdrs",
    srcs = [
        "byte_swap_array.h",
        "command_line_flags.h",
        "device_name_utils.h",
        "env_var.h",
        "stat_summarizer_options.h",
        "stats_calculator.h",
        "use_cudnn.h",
    ],
)

filegroup(
    name = "framework_internal_impl_srcs",
    srcs = [
        "use_cudnn.cc",
    ],
)

filegroup(
    name = "lib_internal_public_hdrs",
    srcs = [
        "command_line_flags.h",
        "env_var.h",
        "use_cudnn.h",
    ],
    visibility = internal_visibility([
        "//tensorflow/core:__pkg__",
        "//tensorflow/core/util:__pkg__",
    ]),
)

filegroup(
    name = "determinism_hdr",
    srcs = [
        "determinism.h",
    ],
    compatible_with = get_compatible_with_portable(),
    visibility = internal_visibility([
        "//tensorflow:__subpackages__",
        "//tensorflow/core/util:__pkg__",
    ]),
)

filegroup(
    name = "framework_srcs",
    srcs = [
        "device_name_utils.h",
        "stat_summarizer_options.h",
        "use_cudnn.h",
    ],
)

filegroup(
    name = "xla_cpu_runtime_hdrs",
    srcs = [
        "safe_reinterpret_cast.h",
    ],
    compatible_with = get_compatible_with_portable(),
)

filegroup(
    name = "xla_cpu_runtime_srcs",
    srcs = [],
    compatible_with = get_compatible_with_portable(),
)

cc_library(
    name = "byte_swap_array",
    srcs = ["byte_swap_array.cc"],
    hdrs = ["byte_swap_array.h"],
    deps = [
        ":safe_reinterpret_cast",
        "//xla/tsl/platform:byte_order",
        "//xla/tsl/platform:errors",
        "//xla/tsl/platform:status",
    ],
)

cc_library(
    name = "determinism_hdr_lib",
    hdrs = [":determinism_hdr"],
    compatible_with = get_compatible_with_portable(),
    # TODO(b/298501506): narrow this in a way that won't break TAP
    visibility = ["//visibility:public"],
)

# Note: This rule should not be used as a dependency for kernels. Use the
# "determinism_for_kernels" rule below instead.
cc_library(
    name = "determinism",
    srcs = ["determinism.cc"],
    hdrs = ["determinism.h"],
    copts = tsl_copts(),
    visibility = internal_visibility(["//tensorflow:__subpackages__"]),
    deps = [
        ":env_var",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
    ],
    alwayslink = 1,
)

# This alias should be used as a dependency for kernels which use determinism,
# as well any other rules which are in the same shared library as the kernels.
# This rule does not include the determinism.cc file for nonstatic builds. The
# reason is that for nonstatic builds, the shared object which contains the
# kernels (e.g. _pywrap_tensorflow_internal.so) must not contain the global
# variable in determinism.cc, since the global variable is already in
# libtensorflow_framework.so.
#
# To test that determinism.cc is not improperly included in the shared object
# which contains the kernels, you can run the "determinism_check_deps" rule
# below.
alias(
    name = "determinism_for_kernels",
    actual = if_static(":determinism", ":determinism_hdr_lib"),
    visibility = internal_visibility(["//tensorflow:__subpackages__"]),
)

check_deps(
    name = "determinism_check_deps",
    disallowed_deps = if_static(
        [],
        otherwise = [":determinism"],
    ),
    deps = [
    ],
)

cc_library(
    name = "determinism_test_util",
    hdrs = [":determinism_test_util.h"],
    data = [
        # Adding this data dependency ensures determinism_check_deps is run
        # whenever determinism tests are run.
        ":determinism_check_deps",
    ],
    deps = [":determinism"],
)

cc_library(
    name = "env_var",
    srcs = ["env_var.cc"],
    hdrs = ["env_var.h"],
    deps = [
        "//xla/tsl/platform:errors",
        "//xla/tsl/platform:logging",
        "//xla/tsl/platform:status",
        "//xla/tsl/platform:types",
        "@local_tsl//tsl/platform:numbers",
        "@local_tsl//tsl/platform:str_util",
        "@local_tsl//tsl/platform:strcat",
        "@local_tsl//tsl/platform:stringpiece",
    ],
)

cc_library(
    name = "reporter",
    srcs = ["reporter.cc"],
    hdrs = ["reporter.h"],
    visibility = internal_visibility([
        "//tensorflow/core:__subpackages__",
        "@local_tsl//tsl:__subpackages__",
    ]),
    deps = [
        "//xla/tsl/platform:env",
        "//xla/tsl/platform:env_impl",
        "//xla/tsl/platform:errors",
        "//xla/tsl/platform:macros",
        "//xla/tsl/platform:types",
        "//xla/tsl/protobuf:test_log_proto_cc",
        "@local_tsl//tsl/platform:str_util",
    ],
)

cc_library(
    name = "stats_calculator_portable",
    srcs = [
        "stats_calculator.cc",
    ],
    hdrs = [
        "stat_summarizer_options.h",
        "stats_calculator.h",
    ],
    copts = tsl_copts(),
    visibility = internal_visibility([
        "//xla/tsl:internal",
        "//xla/tsl/profiler:friends",
    ]),
)

tsl_cc_test(
    name = "stats_calculator_test",
    srcs = ["stats_calculator_test.cc"],
    deps = [
        ":stats_calculator_portable",
        "//xla/tsl/platform:test",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "device_name_utils",
    srcs = ["device_name_utils.cc"],
    hdrs = ["device_name_utils.h"],
    deps = [
        "//xla/tsl/platform:errors",
        "//xla/tsl/platform:status",
        "@local_tsl//tsl/platform:str_util",
        "@local_tsl//tsl/platform:stringpiece",
    ],
)

tsl_cc_test(
    name = "device_name_utils_test",
    size = "small",
    srcs = ["device_name_utils_test.cc"],
    deps = [
        ":device_name_utils",
        "//xla/tsl/lib/core:status_test_util",
        "//xla/tsl/platform:errors",
        "//xla/tsl/platform:test",
        "//xla/tsl/platform:test_benchmark",
        "//xla/tsl/platform:test_main",
        "@com_google_absl//absl/strings",
        "@local_tsl//tsl/platform:strcat",
    ],
)

cc_library(
    name = "command_line_flags",
    srcs = ["command_line_flags.cc"],
    hdrs = ["command_line_flags.h"],
    deps = [
        "//xla/tsl/platform:logging",
        "//xla/tsl/platform:types",
        "@com_google_absl//absl/strings",
        "@local_tsl//tsl/platform:str_util",
        "@local_tsl//tsl/platform:stringpiece",
        "@local_tsl//tsl/platform:stringprintf",
    ],
)

filegroup(
    name = "test_hdrs",
    testonly = 1,
    srcs = [
        "reporter.h",
    ],
    visibility = internal_visibility(["//tensorflow/core/util:__pkg__"]),
)

filegroup(
    name = "onednn_util_hdrs",
    srcs = [
        "onednn_threadpool.h",
    ],
    visibility = internal_visibility([
        "//xla:__subpackages__",
        "//tensorflow/core:__pkg__",
        "//tensorflow/core/framework:__pkg__",
        "//tensorflow/core/util:__pkg__",
    ]),
)

filegroup(
    name = "android_test_hdrs",
    testonly = 1,
    srcs = [
        "reporter.h",
    ],
    visibility = internal_visibility([
        "//tensorflow/core:__pkg__",
        "//tensorflow/core/util:__pkg__",
    ]),
)

filegroup(
    name = "android_test_srcs",
    testonly = 1,
    srcs = [
        "reporter.cc",
        ":android_test_hdrs",
    ],
    visibility = internal_visibility([
        "//tensorflow/core:__pkg__",
        "//tensorflow/core/util:__pkg__",
    ]),
)

cc_library(
    name = "fixed_option_set_flag",
    srcs = ["fixed_option_set_flag.cc"],
    hdrs = ["fixed_option_set_flag.h"],
    deps = [
        "@com_google_absl//absl/base:no_destructor",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/log:check",
        "@com_google_absl//absl/strings",
    ],
)

tsl_cc_test(
    name = "fixed_option_set_flag_test",
    srcs = ["fixed_option_set_flag_test.cc"],
    deps = [
        ":fixed_option_set_flag",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "safe_reinterpret_cast",
    hdrs = ["safe_reinterpret_cast.h"],
)

tsl_cc_test(
    name = "safe_reinterpret_cast_test",
    srcs = ["safe_reinterpret_cast_test.cc"],
    deps = [
        ":safe_reinterpret_cast",
        "@com_google_googletest//:gtest_main",
    ],
)
