cmake_minimum_required(VERSION 3.22)
project(ros_tensorrt_bridge)
#project(ros_tensorrt_bridge CXX CUDA)
#cmake_policy(SET CMP0146 NEW)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(RedBold    "${Esc}[31;1m")
  set(GreenBold  "${Esc}[32;1m")
  set(YellowBold "${Esc}[33;1m")
endif()


# ---------------------- CUDA & TensorRT ----------------------
set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
enable_language(CUDA)


# include and link dirs of cuda and tensorrt, you need adapt them if yours are different
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  message("${GreenBold}Target platform is aarch64${ColourReset}")
  include_directories(/usr/local/cuda/targets/aarch64-linux/include)
  link_directories(/usr/local/cuda/targets/aarch64-linux/lib)
else()
  message("${GreenBold}Target platform is x86_64${ColourReset}")

  # cuda
  include_directories(/usr/local/cuda/include)
  link_directories(/usr/local/cuda/lib64)

  # tensorrt
  #include_directories(/workspace/shared/TensorRT-10/include)
  #link_directories(/workspace/shared/TensorRT-10/lib)
endif()
# ---------------------- CUDA ----------------------


# ----------------------- Dependencies -----------------------
# find dependencies
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(CUDAToolkit REQUIRED)
find_package(OpenCV REQUIRED)
# ----------------------- Dependencies -----------------------


add_subdirectory(yolo-tensorrt10)

add_executable(main_test src/main_test.cpp)
target_link_libraries(main_test yolo11)





ament_package()

