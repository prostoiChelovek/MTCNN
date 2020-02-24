find_package(OpenCV 4 REQUIRED)

option(USE_TENSORFLOW "Use tensorflow" ON)
option(USE_CAFFE "Use caffe" OFF)
option(USE_MXNET "Use mxnet" OFF)

set(LIB_SOURCES mtcnn.cpp utils.cpp comm_lib.cpp)

if (USE_TENSORFLOW)
    find_package(TensorFlow REQUIRED)
    set(PROJECT_INCLUDE_DIRS ${TensorFlow_INCLUDE_DIRS})
    set(PROJECT_LIBRARIES ${TensorFlow_LIBRARIES})

    set(LIB_SOURCES ${LIB_SOURCES} tensorflow_mtcnn.cpp)
endif ()

message("${LIB_SOURCES}")

add_library(mtcnn STATIC ${LIB_SOURCES})

include_directories(../include)
include_directories(${PROJECT_INCLUDE_DIRS})

target_link_libraries(mtcnn ${PROJECT_LIBRARIES})
target_link_libraries(mtcnn ${OpenCV_LIBS})
