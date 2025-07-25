load("//tensorflow:strict.default.bzl", "py_strict_binary", "py_strict_library", "py_strict_test")
load("//tensorflow:tensorflow.default.bzl", "cuda_py_strict_test")

package(
    # copybara:uncomment default_applicable_licenses = ["//tensorflow:license"],
    default_visibility = ["//tensorflow:internal"],
    licenses = ["notice"],
)

py_strict_library(
    name = "op_callbacks_common",
    srcs = ["op_callbacks_common.py"],
)

py_strict_library(
    name = "check_numerics_callback",
    srcs = ["check_numerics_callback.py"],
    deps = [
        ":op_callbacks_common",
        ":source_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:monitoring",
        "//tensorflow/python/framework:op_callbacks",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:debug_ops_gen",
        "//tensorflow/python/platform:tf_logging",
        "//tensorflow/python/util:compat",
        "//tensorflow/python/util:object_identity",
        "//tensorflow/python/util:tf_export",
        "//third_party/py/numpy",
    ],
)

py_strict_library(
    name = "dumping_callback",
    srcs = ["dumping_callback.py"],
    deps = [
        ":debug_events_writer",
        ":op_callbacks_common",
        ":source_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:function",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:op_callbacks",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:tensor_util",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:debug_ops_gen",
        "//tensorflow/python/platform:tf_logging",
        "//tensorflow/python/util:compat",
        "//tensorflow/python/util:object_identity",
        "//tensorflow/python/util:tf_export",
        "//tensorflow/python/util:tf_stack",
    ],
)

py_strict_library(
    name = "dumping_callback_test_lib",
    srcs = ["dumping_callback_test_lib.py"],
    deps = [
        ":check_numerics_callback",
        ":debug_events_reader",
        ":dumping_callback",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/framework:versions",
    ],
)

py_strict_library(
    name = "common",
    srcs = ["common.py"],
)

py_strict_library(
    name = "debug_events_reader",
    srcs = ["debug_events_reader.py"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:tensor_util",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/lib/io:tf_record",
        "//tensorflow/python/util:compat",
    ],
)

py_strict_library(
    name = "debug_events_monitors",
    srcs = ["debug_events_monitors.py"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//third_party/py/numpy",
    ],
)

py_strict_library(
    name = "debug_events_writer",
    srcs = ["debug_events_writer.py"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:_pywrap_debug_events_writer",
    ],
)

py_strict_library(
    name = "debug_graphs",
    srcs = ["debug_graphs.py"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:op_def_registry",
        "//tensorflow/python/platform:tf_logging",
    ],
)

py_strict_library(
    name = "debug_data",
    srcs = ["debug_data.py"],
    visibility = [
        "//tensorflow:internal",
        "//third_party/py/tf_slim:__subpackages__",
        "//waymo/ml/deploy/numeric_debugging:__subpackages__",
    ],
    deps = [
        ":debug_graphs",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/core/framework:graph_proto_py_proto",
        "//tensorflow/core/util:event_proto_py_proto",
        "//tensorflow/python/framework:tensor_util",
        "//tensorflow/python/platform:gfile",
        "//tensorflow/python/platform:tf_logging",
        "//tensorflow/python/util:compat",
        "//third_party/py/numpy",
    ],
)

py_strict_library(
    name = "debug_gradients",
    srcs = ["debug_gradients.py"],
    deps = [
        ":debug_data",
        ":debug_graphs",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:tensor",
        "//tensorflow/python/ops:array_ops_gen",
        "//tensorflow/python/ops:variables",
    ],
)

py_strict_library(
    name = "debug_utils",
    srcs = ["debug_utils.py"],
)

py_strict_binary(
    name = "grpc_tensorflow_server",
    srcs = ["grpc_tensorflow_server.py"],
    deps = [
        ":grpc_tensorflow_server_lib",
        "//tensorflow/python/training:server_lib",
    ],
)

py_strict_library(
    name = "grpc_tensorflow_server_lib",
    srcs = [
        "grpc_tensorflow_server.py",
    ],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/platform:tf_logging",
        "//tensorflow/python/training:server_lib",
        "@absl_py//absl:app",
    ],
)

py_strict_library(
    name = "source_utils",
    srcs = ["source_utils.py"],
    deps = [
        ":profiling",
        "//third_party/py/numpy",
        "@absl_py//absl:app",
    ],
)

py_strict_library(
    name = "source_remote",
    srcs = ["source_remote.py"],
    deps = [
        ":common",
        ":debug_service_pb2_grpc",
        ":source_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/core/debug:debug_service_proto_py",
        "//tensorflow/python/platform:gfile",
        "//tensorflow/python/profiler:tfprof_logger",
    ],
)

py_strict_library(
    name = "profiling",
    srcs = ["profiling.py"],
)

py_strict_test(
    name = "common_test",
    size = "small",
    srcs = ["common_test.py"],
    deps = [
        ":common",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/platform:test",
    ],
)

py_strict_test(
    name = "debug_events_monitors_test",
    size = "medium",
    srcs = ["debug_events_monitors_test.py"],
    tags = [
        "no_windows",  # b/142475891
    ],
    deps = [
        ":debug_events_monitors",
        ":debug_events_reader",
        ":dumping_callback",
        ":dumping_callback_test_lib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:test",
        "//third_party/py/numpy",
        "@absl_py//absl/testing:parameterized",
    ],
)

py_strict_test(
    name = "debug_events_writer_test",
    size = "medium",
    srcs = ["debug_events_writer_test.py"],
    tags = [
        "no_windows",  # b/142475891
    ],
    deps = [
        ":debug_events_reader",
        ":debug_events_writer",
        ":dumping_callback_test_lib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/framework:versions",
        "//tensorflow/python/platform:test",
        "@absl_py//absl/testing:parameterized",
    ],
)

py_strict_test(
    name = "debug_graphs_test",
    size = "small",
    srcs = ["debug_graphs_test.py"],
    deps = [
        ":debug_graphs",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/platform:client_testlib",
    ],
)

py_strict_test(
    name = "debug_data_test",
    size = "small",
    srcs = ["debug_data_test.py"],
    tags = ["no_windows"],  # TODO(b/184424727): Enable this test on Windows.
    deps = [
        ":debug_data",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/core/framework:graph_proto_py_proto",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:gfile",
        "//tensorflow/python/platform:test",
        "//third_party/py/numpy",
    ],
)

cuda_py_strict_test(
    name = "check_numerics_callback_test",
    size = "medium",
    srcs = ["check_numerics_callback_test.py"],
    tags = [
        "no_mac",  # TODO(b/175322370): Detected Infinity or NaN in output 0 of graph op "RealDiv"
        "no_windows",
    ],
    deps = [
        ":check_numerics_callback",
        "//tensorflow/python/data/ops:dataset_ops",
        "//tensorflow/python/eager:backprop",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:array_grad",
        "//tensorflow/python/ops:custom_gradient",
        "//tensorflow/python/ops:gradient_checker_v2",
        "//tensorflow/python/ops:math_grad",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:nn_ops_gen",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:test",
        "//third_party/py/numpy",
    ],
)

cuda_py_strict_test(
    name = "dumping_callback_test",
    size = "medium",
    srcs = ["dumping_callback_test.py"],
    shard_count = 4,
    tags = [
        "no_windows",  # TODO(b/142475891): Enable this test on Windows.
    ],
    xla_enable_strict_auto_jit = False,  # Node names are different with autojit
    deps = [
        ":debug_events_reader",
        ":dumping_callback",
        ":dumping_callback_test_lib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:context",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/platform:tf_logging",
        "//third_party/py/numpy",
        "@absl_py//absl/testing:parameterized",
    ],
)

cuda_py_strict_test(
    name = "debug_v2_ops_test",
    size = "medium",
    srcs = ["debug_v2_ops_test.py"],
    tags = ["no_windows_gpu"],
    deps = [
        ":debug_events_reader",
        ":debug_events_writer",
        ":dumping_callback_test_lib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/eager:def_function",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:dtypes",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:tensor_util",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:debug_ops_gen",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/platform:test",
        "//third_party/py/numpy",
    ],
)

cuda_py_strict_test(
    name = "debug_gradients_test",
    size = "small",
    srcs = ["debug_gradients_test.py"],
    xla_enable_strict_auto_jit = False,  # Node names are different with autojit
    deps = [
        ":debug_data",
        ":debug_gradients",
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:tensor",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:gradients_impl",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/training:gradient_descent",
    ],
)

py_strict_test(
    name = "debug_utils_test",
    size = "small",
    srcs = ["debug_utils_test.py"],
    deps = [
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:resource_variable_ops",
        "//tensorflow/python/ops:variable_v1",
        "//tensorflow/python/platform:test",
        "//third_party/py/numpy",
    ],
)

py_strict_test(
    name = "source_utils_test",
    size = "small",
    srcs = ["source_utils_test.py"],
    tags = [
        "no_windows",
    ],
    deps = [
        ":debug_data",
        ":debug_utils",
        ":source_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:resource_variable_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/ops:while_loop",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/util:tf_inspect",
        "//third_party/py/numpy",
    ],
)

py_strict_test(
    name = "source_remote_test",
    size = "small",
    srcs = ["source_remote_test.py"],
    tags = [
        "no_windows",
        "oss_serial",
    ],
    deps = [
        ":grpc_debug_test_server",
        ":source_remote",
        ":source_utils",
        "//tensorflow/core/debug:debug_service_proto_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:resource_variable_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/util:tf_inspect",
    ],
)

py_strict_test(
    name = "profiling_test",
    size = "small",
    srcs = ["profiling_test.py"],
    deps = [
        ":profiling",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/platform:test",
    ],
)

py_strict_library(
    name = "session_debug_testlib",
    srcs = ["session_debug_testlib.py"],
    deps = [
        ":debug_data",
        ":debug_graphs",
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/framework:for_generated_wrappers",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:array_ops",
        "//tensorflow/python/ops:cond",
        "//tensorflow/python/ops:control_flow_ops",
        "//tensorflow/python/ops:data_flow_ops",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:parsing_ops",
        "//tensorflow/python/ops:rnn",
        "//tensorflow/python/ops:rnn_cell_impl",
        "//tensorflow/python/ops:state_ops",
        "//tensorflow/python/ops:tensor_array_grad",
        "//tensorflow/python/ops:variable_v1",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/ops:while_loop",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/platform:test",
        "//tensorflow/python/training:gradient_descent",
        "//third_party/py/numpy",
    ],
)

py_strict_library(
    name = "debug_service_pb2_grpc",
    srcs = ["debug_service_pb2_grpc.py"],
    deps = [
        "//tensorflow/core:protos_all_py",
        "//tensorflow/core/debug:debug_service_proto_py",
    ],
)

py_strict_library(
    name = "grpc_debug_server",
    srcs = ["grpc_debug_server.py"],
    visibility = ["//visibility:public"],
    deps = [
        ":debug_graphs",
        ":debug_service_pb2_grpc",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/core/debug:debug_service_proto_py",
        "//tensorflow/python/platform:tf_logging",
        "//tensorflow/python/util:compat",
    ],
)

py_strict_library(
    name = "grpc_debug_test_server",
    srcs = ["grpc_debug_test_server.py"],
    deps = [
        ":debug_data",
        ":debug_utils",
        ":grpc_debug_server",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/core/debug:debug_service_proto_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:errors",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/util:compat",
        "@pypi_portpicker//:pkg",
    ],
)

cuda_py_strict_test(
    name = "debug_grappler_test",
    size = "small",
    srcs = ["debug_grappler_test.py"],
    xla_enable_strict_auto_jit = False,  # Tests TF:Classic implementation.
    deps = [
        ":debug_data",
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:for_generated_wrappers",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:variable_v1",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:test",
    ],
)

cuda_py_strict_test(
    name = "session_debug_file_test",
    size = "small",
    srcs = ["session_debug_file_test.py"],
    tags = ["notsan"],
    xla_enable_strict_auto_jit = False,  # Node names are different with autojit
    deps = [
        ":debug_data",
        ":debug_utils",
        ":session_debug_testlib",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:for_generated_wrappers",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:variable_v1",
        "//tensorflow/python/platform:test",
    ],
)

cuda_py_strict_test(
    name = "debug_graph_reconstruction_test",
    size = "small",
    srcs = ["debug_graph_reconstruction_test.py"],
    xla_enable_strict_auto_jit = False,  # Node names are different with autojit
    deps = [
        ":debug_data",
        ":debug_graphs",
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:constant_op",
        "//tensorflow/python/framework:ops",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:cond",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/ops:while_loop",
        "//tensorflow/python/platform:client_testlib",
        "//tensorflow/python/training:gradient_descent",
    ],
)

cuda_py_strict_test(
    name = "session_debug_multi_gpu_test",
    size = "small",
    srcs = ["session_debug_multi_gpu_test.py"],
    tags = [
        "no_windows",  # TODO(b/184424727): Re-enable this.
        "no_windows_gpu",
    ],
    xla_enable_strict_auto_jit = False,  # Node names are different with autojit
    deps = [
        ":debug_data",
        ":debug_utils",
        "//tensorflow/core:protos_all_py",
        "//tensorflow/python/client:device_lib",
        "//tensorflow/python/client:session",
        "//tensorflow/python/framework:for_generated_wrappers",
        "//tensorflow/python/framework:test_lib",
        "//tensorflow/python/lib/io:file_io",
        "//tensorflow/python/ops:math_ops",
        "//tensorflow/python/ops:variables",
        "//tensorflow/python/platform:test",
    ],
)
