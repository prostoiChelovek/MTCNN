cmake_minimum_required(VERSION 3.8)
project(mtcnn)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libmtcnn)

set(SOURCE_FILES camera.cpp)
add_executable(run ${SOURCE_FILES})

include_directories(include)

target_link_libraries(run mtcnn)
target_link_libraries(run ${OpenCV_LIBS})
