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

if (USE_CAFFE)
    message(WARNING "Caffe backend wasn`t tested")

    find_package(Caffe REQUIRED)
    set(PROJECT_LIBRARIES ${Caffe_LIBRARIES})

    set(LIB_SOURCES ${LIB_SOURCES} caffe_mtcnn.cpp)
endif()

if (USE_MXNET)
    message(WARNING "MxNet backend wasn`t tested")

    find_package(MxNet REQUIRED)
    set(PROJECT_INCLUDE_DIRS ${MxNet_INCLUDE_DIRS})
    set(PROJECT_LIBRARIES ${MxNet_LIB})
endif ()

add_library(mtcnn STATIC ${LIB_SOURCES})

include_directories(../include)
include_directories(${PROJECT_INCLUDE_DIRS})

target_link_libraries(mtcnn ${PROJECT_LIBRARIES})
target_link_libraries(mtcnn ${OpenCV_LIBS})
