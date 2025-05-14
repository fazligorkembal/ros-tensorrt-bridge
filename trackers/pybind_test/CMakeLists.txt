cmake_minimum_required(VERSION 3.14)
project(ConvertGreyExample)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(pybind11 REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE pybind11::embed pybind11::module ${OpenCV_LIBS})

#add_library(pybind_detections detections.cpp)
#target_link_libraries(pybind_detections PRIVATE pybind11::module ${OpenCV_LIBS})
pybind11_add_module(
    pybind_detections
    MODULE
    detections.cpp
)