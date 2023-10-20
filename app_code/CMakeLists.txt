cmake_minimum_required(VERSION 3.16)

project(gstreamer_01) #Project name
set(CMAKE_CXX_STANDARD 14) #setting C++ 14 standard

find_package(PkgConfig) #finding pkg-config is a helper tool
find_package(CUDA  REQUIRED)
find_package(OpenCV REQUIRED)

#using pkg-config to getting Gstreamer
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(YOLOV5_TENSORRT yolov5-tensorrt)

#including header files directory
include_directories(
        ${GLIB_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
        ${YOLOV5_TENSORRT_INCLUDE_DIRS}
        ${CUDA_INCLUDE_DIRS}
)

#linking libraries directories
link_directories(
        ${GLIB_LIBRARY_DIRS}
        ${GSTREAMER_LIBRARY_DIRS}
        ${YOLOV5_TENSORRT_LIBRARIES}
)

#building target executable
add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
        ${OpenCV_INCLUDE_DIRS} 
        ${CUDA_INCLUDE_DIRS}
)

#linking libraries with target executable
target_link_libraries(${PROJECT_NAME} 
    ${GSTREAMER_LIBRARIES}
    yolov5-tensorrt 
    nvinfer
    nvonnxparser
    ${CUDA_CUDART_LIBRARY}
    ${OpenCV_LIBRARIES}
)
