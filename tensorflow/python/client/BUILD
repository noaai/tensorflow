load("@rules_cc//cc:cc_library.bzl", "cc_library")

# Contains targets that expose client session APIs
load("//tensorflow:strict.default.bzl", "py_strict_library")
load("//tensorflow:tensorflow.bzl", "tf_cuda_library")
load("//tensorflow:tensorflow.default.bzl", "cuda_py_strict_test", "tf_py_strict_test", "tf_python_pybind_extension")
load("//tensorflow/core/platform:build_config_root.bzl", "if_pywrap", "if_static")
load(
    "//tensorflow/tools/test:performance.bzl",
    "cuda_py_benchmark_test",
)

package(
    # copybara:uncomment default_applicable_licenses = ["//tensorflow:license"],
    default_visibility = [
        "//tensorflow:internal",
    ],
    licenses = ["notice"],
)

py_strict_library(
    name = "pywrap_tf_session",
    srcs = ["pywrap_tf_session.py"],
    visibility = ["//visibility:public"],
    deps = [
        ":_pywrap_tf_session",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python/util:tf_stack",
    ],
)

tf_python_pybind_extension(
    name = "_pywrap_tf_session",
    srcs = ["tf_session_wrapper.cc"],
    hdrs = if_pywrap(
        if_false = [
            "tf_session_helper.h",
            "//tensorflow/c:headers",
            "//tensorflow/c:safe_ptr_hdr",
            "//tensorflow/c/eager:headers",
            "//tensorflow/c/eager:pywrap_required_hdrs",
            "//tensorflow/c/experimental/ops:pywrap_required_hdrs",
            "@local_xla//xla/tsl/distributed_runtime:pywrap_required_hdrs",
            "@local_xla//xla/tsl/distributed_runtime/coordination:pywrap_required_hdrs",
            "@local_xla//xla/tsl/python/lib/core:numpy_hdr",
            "//tensorflow/core/common_runtime/eager:pywrap_required_hdrs",
            "//tensorflow/core/distributed_runtime:pywrap_required_hdrs",
            "//tensorflow/core/distributed_runtime/coordination:pywrap_required_hdrs",
            "//tensorflow/core/distributed_runtime/eager:pywrap_required_hdrs",
            "//tensorflow/python/lib/core:safe_pyobject_ptr_required_hdrs",
        ],
        if_true = [],
    ),
    additional_exported_symbols = [
        "_TF_SetTarget",
        "_TF_SetConfig",
        "_TF_NewSessionOptions",
    ],
    enable_stub_generation = True,
    pytype_srcs = [
        "_pywrap_tf_session.pyi",
    ],
    deps = [
        "//tensorflow/c:pywrap_required_hdrs",
        "//tensorflow/core:framework_headers_lib",
        "//tensorflow/core:lib_headers_for_pybind",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core/common_runtime:core_cpu_headers_lib",
        "//tensorflow/core/config:flags_headers",
        "//tensorflow/core/framework:pywrap_required_hdrs",
        "//tensorflow/core/lib/llvm_rtti",
        "//tensorflow/core/public:release_version",
        "//tensorflow/core/util:version_info",
        "//tensorflow/python/lib/core:pybind11_lib",
        "//tensorflow/python/lib/core:pybind11_status",
        "//tensorflow/python/lib/core:safe_pyobject_ptr",
        "//third_party/py/numpy:headers",
        "@com_google_absl//absl/types:optional",
        "@eigen_archive//:eigen3",
        "@local_xla//third_party/python_runtime:headers",
        "@local_xla//xla/tsl/python/lib/core:numpy",
        "@pybind11",
        "@pybind11_abseil//pybind11_abseil:absl_casters",
        "@pybind11_protobuf//pybind11_protobuf:native_proto_caster",
    ] + if_pywrap([
        "//tensorflow/c:safe_ptr",
        "//tensorflow/c:c_api_experimental",
        "//tensorflow/python/client:tf_session_helper",
        "//tensorflow/c:python_api",
        "//tensorflow/core/common_runtime:core_cpu_lib",
    ]) + if_static(
        extra_deps = [
            "//tensorflow/core/protobuf:eager_service_proto_cc",
            "//tensorflow/core/protobuf:master_proto_cc",
            "//tensorflow/core/protobuf:worker_proto_cc",
            "//tensorflow/core:version_lib",
            "@local_xla//xla/tsl/protobuf:coordination_service_proto_cc",
        ],
        otherwise = [
            "//tensorflow/core/protobuf:eager_service_proto_cc_headers_only",
            "//tensorflow/core/protobuf:master_proto_cc_headers_only",
            "//tensorflow/core/protobuf:worker_proto_cc_headers_only",
            "@local_xla//xla/tsl/protobuf:coordination_service_proto_cc_headers_only",
        ],
    ),
)

tf_python_pybind_extension(
    name = "_pywrap_debug_events_writer",
    srcs = ["debug_events_writer_wrapper.cc"],
    enable_stub_generation = True,
    pytype_srcs = [
        "_pywrap_debug_events_writer.pyi",
    ],
    deps = [
        "//tensorflow/core:framework",
        "//tensorflow/core:framework_headers_lib",
        "//tensorflow/core:lib",
        "//tensorflow/core:lib_headers_for_pybind",
        "//tensorflow/core:lib_proto_parsing",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/python/lib/core:pybind11_absl",
        "//tensorflow/python/lib/core:pybind11_proto",
        "//tensorflow/python/lib/core:pybind11_status",
        "@com_google_absl//absl/strings",
        "@local_xla//third_party/python_runtime:headers",
        "@pybind11",
    ],
)

tf_python_pybind_extension(
    name = "_pywrap_events_writer",
    srcs = ["events_writer_wrapper.cc"],
    enable_stub_generation = True,
    pytype_srcs = [
        "_pywrap_events_writer.pyi",
    ],
    deps = [
        "//tensorflow/core:framework",
        "//tensorflow/core:framework_headers_lib",
        "//tensorflow/core:lib_headers_for_pybind",
        "//tensorflow/core:lib_proto_parsing",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/python/lib/core:pybind11_absl",
        "//tensorflow/python/lib/core:pybind11_proto",
        "//tensorflow/python/lib/core:pybind11_status",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@local_xla//third_party/python_runtime:headers",
        "@pybind11",
    ],
)

py_strict_library(
    name = "client",
    srcs = ["client_lib.py"],
    deps = [
        ":_pywrap_device_lib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/platform:build_info",
        "//tensorflow/python/platform:tf_logging",
    ],
)

tf_py_strict_test(
    name = "events_writer_test",
    size = "small",
    srcs = ["events_writer_test.py"],
    deps = [
        ":_pywrap_events_writer",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:pywrap_tensorflow",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:tf_record",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/util:compat",
    ],
)

py_strict_library(
    name = "device_lib",
    srcs = ["device_lib.py"],
    visibility = [
        "//tensorflow:internal",
        "//third_party/mlperf/submissions/training/v0_7/models:__subpackages__",
        "//third_party/py/cleverhans:__subpackages__",
    ],
    deps = [
        ":_pywrap_device_lib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python:pywrap_tensorflow",
    ],
)

tf_python_pybind_extension(
    name = "_pywrap_device_lib",
    srcs = ["device_lib_wrapper.cc"],
    enable_stub_generation = True,
    pytype_srcs = [
        "_pywrap_device_lib.pyi",
    ],
    deps = [
        "//tensorflow/core:core_cpu",
        "//tensorflow/core:framework_internal_headers_lib",
        "//tensorflow/core:lib_proto_parsing",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core/common_runtime:core_cpu_headers_lib",
        "//tensorflow/core/common_runtime:device",
        "//tensorflow/core/common_runtime:device_factory",
        "//tensorflow/python/lib/core:pybind11_proto",
        "//tensorflow/python/lib/core:pybind11_status",
        "@local_xla//third_party/python_runtime:headers",
        "@pybind11",
    ],
)

cuda_py_strict_test(
    name = "device_lib_test",
    size = "small",
    srcs = [
        "device_lib_test.py",
    ],
    deps = [
        ":device_lib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:test",
    ],
)

cc_library(
    name = "session_ref",
    srcs = ["session_ref.cc"],
    hdrs = ["session_ref.h"],
    deps = [
        "//tensorflow/core:core_cpu",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core/protobuf:replay_log_proto_cc",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
    ] + if_static(
        extra_deps = [
            "//tensorflow/core/protobuf:master_proto_cc",
        ],
        otherwise = [
            "//tensorflow/core/protobuf:master_proto_cc_headers_only",
        ],
    ),
)

tf_cuda_library(
    name = "tf_session_helper",
    srcs = ["tf_session_helper.cc"],
    hdrs = ["tf_session_helper.h"],
    compatible_with = [],
    deps = [
        ":construction_fails_op",
        ":session_ref",
        "//tensorflow/c:c_api",
        "//tensorflow/c:c_api_internal",
        "//tensorflow/c:safe_ptr",
        "//tensorflow/c:tf_buffer_internal",
        "//tensorflow/c:tf_status_helper",
        "//tensorflow/core",
        "//tensorflow/core:all_kernels",
        "//tensorflow/core:core_cpu_base",
        "//tensorflow/core:direct_session",
        "//tensorflow/core:framework",
        "//tensorflow/core:framework_internal",
        "//tensorflow/core:graph",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/python/framework:test_ops_kernels",
        "//tensorflow/python/lib/core:ndarray_tensor",
        "//tensorflow/python/lib/core:ndarray_tensor_bridge",
        "//tensorflow/python/lib/core:safe_pyobject_ptr",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@local_xla//xla/tsl/python/lib/core:numpy",
    ],
    alwayslink = 1,
)

py_strict_library(
    name = "session",
    srcs = ["session.py"],
    # copybara:uncomment_begin(google-only)
    # visibility = [
    # "//third_party/cloud_tpu/convergence_tools:__subpackages__",
    # "//third_party/py/tf_slim:__subpackages__",
    # "//tensorflow:internal",
    # ],
    # copybara:uncomment_end_and_comment_begin
    visibility = [
        "//visibility:public",
    ],
    # copybara:comment_end
    deps = [
        ":pywrap_tf_session",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:monitoring",
        "//tensorflow/python/framework:device",
        "//tensorflow/python/framework:error_interpolation",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:indexed_slices",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:sparse_tensor",
        "//tensorflow/python/framework:stack",
        "//tensorflow/python/framework:tensor",
        "//tensorflow/python/ops:session_ops",
        "//tensorflow/python/platform:tf_logging",
        "//tensorflow/python/training/experimental:mixed_precision_global_state",
        "//tensorflow/python/util:compat",
        "//tensorflow/python/util:deprecation",
        "//tensorflow/python/util:nest",
        "//tensorflow/python/util:numpy_compat",
        "//tensorflow/python/util:tf_export",
        "//third_party/py/numpy",
        "@pypi_wrapt//:pkg",
    ],
)

py_strict_library(
    name = "timeline",
    srcs = ["timeline.py"],
    visibility = ["//visibility:public"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/platform:build_info",
        "//tensorflow/python/platform:tf_logging",
    ],
)

# Just used by tests.
tf_cuda_library(
    name = "construction_fails_op",
    srcs = ["test_construction_fails_op.cc"],
    deps = [
        "//tensorflow/core",
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
    ],
    alwayslink = 1,
)

tf_py_strict_test(
    name = "session_test",
    size = "medium",
    srcs = ["session_test.py"],
    grpc_enabled = True,
    tags = [
        "no_gpu",  # b/127001953
        "no_oss",  # b/198485096
        "no_pip_gpu",  # testInteractivePlacePrunedGraph fails on invalid assumption about GPU ops.
        "no_windows",
    ],
    deps = [
        ":session",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/framework:config",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:device",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:function",
        "//tensorflow/python/framework:importer",
        "//tensorflow/python/framework:indexed_slices",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:sparse_tensor",
        "//tensorflow/python/framework:stack",
        "//tensorflow/python/framework:tensor_util",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/framework:versions",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:control_flow_ops",
        "//tensorflow/python/ops:control_flow_ops_gen",
        "//tensorflow/python/ops:data_flow_ops",
        "//tensorflow/python/ops:gradients",
        "//tensorflow/python/ops:gradients_impl",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:resource_variable_ops",
        "//tensorflow/python/ops:state_ops",
        "//tensorflow/python/ops:variable_v1",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/ops:while_loop",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/training:server_lib",
        "//tensorflow/python/util:compat",
        "//third_party/py/numpy",
        "@six_archive//:six",
    ],
)

tf_py_strict_test(
    name = "session_clusterspec_prop_test",
    size = "small",
    srcs = ["session_clusterspec_prop_test.py"],
    grpc_enabled = True,
    tags = [
        "no_gpu",
        "no_oss",
        "no_pip_gpu",
        "notap",
    ],
    deps = [
        ":session",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:resource_variable_ops",
        "//tensorflow/python/ops:state_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/training:server_lib",
        "//third_party/py/numpy",
    ],
)

tf_py_strict_test(
    name = "session_list_devices_test",
    size = "small",
    srcs = ["session_list_devices_test.py"],
    grpc_enabled = True,
    tags = [
        "no_gpu",
        "no_pip_gpu",
    ],
    deps = [
        ":pywrap_tf_session",
        ":session",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/training:server_lib",
    ],
)

tf_py_strict_test(
    name = "session_partial_run_test",
    size = "small",
    srcs = ["session_partial_run_test.py"],
    grpc_enabled = True,
    tags = [
        "no_gpu",
        "no_rocm",
        "no_windows",
    ],
    deps = [
        ":session",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/training:server_lib",
    ],
)

cuda_py_strict_test(
    name = "timeline_test",
    size = "small",
    srcs = ["timeline_test.py"],
    tags = [
        "gpu_cupti",
        "no_gpu",  # b/154742661
    ],
    xla_enable_strict_auto_jit = False,  # Graph structure is different with autojit
    deps = [
        ":session",
        ":timeline",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:client_testlib",
    ],
)

cuda_py_strict_test(
    name = "virtual_gpu_test",
    size = "small",
    srcs = ["virtual_gpu_test.py"],
    tags = [
        "no_gpu",  # b/127386241
        "no_windows_gpu",
    ],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:random_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:tf_logging",
    ],
)

cuda_py_benchmark_test(
    name = "session_benchmark",
    srcs = ["session_benchmark.py"],
    grpc_enabled = True,
    main = "session_benchmark.py",
    deps = [
        ":session",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:random_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/training:server_lib",
        "//third_party/py/numpy",
    ],
)
