cmake_minimum_required(VERSION 3.22)
project(ros_tensorrt_bridge CXX CUDA)
cmake_policy(SET CMP0146 NEW)

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
# ----------------------- Dependencies -----------------------

include_directories(include)

#add_library(kernel_lib src/kernels/deviceInfo.cpp)
#set_target_properties(kernel_lib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
#target_include_directories(kernel_lib PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
#target_link_libraries(kernel_lib PRIVATE CUDA::cudart)

set(library_name ${PROJECT_NAME}_core)

add_library(${library_name} SHARED src/tensorrt_bridge.cpp src/kernels/deviceInfo.cpp)
target_link_libraries(${library_name} CUDA::cudart)
target_link_libraries(${library_name} nvinfer)


# For adding the header files
install(DIRECTORY include/
  DESTINATION include/
)

# Load the Library
install(
  TARGETS ${library_name}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


ament_export_include_directories(
  include
)
ament_export_libraries(
  ${library_name}
)
ament_export_dependencies(
  CUDAToolkit
)

# ------------------------- Information -------------------------
if(TARGET CUDA::cudart)
  message("${GreenBold}CUDA version: ${CUDAToolkit_VERSION}${ColourReset}")
  message("${Green}Using CUDA compiler: ${CMAKE_CUDA_COMPILER}${ColourReset}")
  message("${Green}CUDAToolkit include directory: ${CUDAToolkit_INCLUDE_DIRS}${ColourReset}")
  include_directories(${CUDA_INCLUDE_DIRS})
  link_directories(${CUDA_LIBRARIES_DIRS})
else()
  message("${RedBold}CUDA not found!${ColourReset}")
endif()
# ------------------------- Information -------------------------



ament_package()

