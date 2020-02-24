# Locates the tensorFlow library and include directories.
# Modified version of https://github.com/cjweeks/tensorflow-cmake

include(FindPackageHandleStandardArgs)
unset(TENSORFLOW_FOUND)

find_path(TensorFlow_INCLUDE_DIR
        NAMES
        tensorflow/core
        tensorflow/cc
        third_party
        HINTS
        /usr/local/include/google/tensorflow
        /usr/include/google/tensorflow
        /usr/local/include/tensorflow
        /usr/include/tensorflow
        $ENV{HOME}/tensorflow/bazel-tensorflow
        $ENV{TF_ROOT}/bazel-tensorflow)

message($ENV{HOME}/tensorflow/bazel-tensorflow/tensorflow)

find_library(TensorFlow_LIBRARY
        NAMES
        tensorflow_all
        tensorflow
        HINTS
        /usr/lib
        /usr/local/lib
        $ENV{HOME}/tensorflow/bazel-bin/tensorflow
        $ENV{TF_ROOT}/bazel-bin/tensorflow)

# set TensorFlow_FOUND
find_package_handle_standard_args(TensorFlow DEFAULT_MSG TensorFlow_INCLUDE_DIR TensorFlow_LIBRARY)

# set external variables for usage in CMakeLists.txt
if (TENSORFLOW_FOUND)
    set(TensorFlow_LIBRARIES ${TensorFlow_LIBRARY})
    set(TensorFlow_INCLUDE_DIRS ${TensorFlow_INCLUDE_DIR})
endif ()

# hide locals from GUI
mark_as_advanced(TensorFlow_INCLUDE_DIR TensorFlow_LIBRARY)