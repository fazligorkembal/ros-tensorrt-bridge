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
  set(Red "${Esc}[31m")
  set(Green "${Esc}[32m")
  set(Yellow "${Esc}[33m")
  set(RedBold "${Esc}[31;1m")
  set(GreenBold "${Esc}[32;1m")
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

include_directories(include)

install(DIRECTORY include/
  DESTINATION include
)

set(library_name ${PROJECT_NAME}_core)


add_library(model_builder src/scratch/model_builder.cpp)
target_link_libraries(model_builder yolo11)

add_library(${library_name} src/tensorrt_bridge.cpp)
target_link_libraries(${library_name} model_builder)

target_include_directories(${library_name}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<TARGET_PROPERTY:yolo11,INTERFACE_INCLUDE_DIRECTORIES> # Araya boşluk KONMAYACAK
)

install(
  TARGETS ${library_name} yolo11 model_builder myplugins
  EXPORT ros_tensorrt_bridge # Kütüphaneyi export et
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include # Header'ları da kur
)

ament_export_targets(ros_tensorrt_bridge HAS_LIBRARY_TARGET)
ament_package()
