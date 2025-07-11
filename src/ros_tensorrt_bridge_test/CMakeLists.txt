cmake_minimum_required(VERSION 3.8)
project(ros_tensorrt_bridge_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
enable_language(CUDA)

include_directories(/usr/local/cuda/include)
link_directories(/usr/local/cuda/lib64)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ros_tensorrt_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Python3 COMPONENTS Development REQUIRED)
find_package(pybind11 REQUIRED)


add_executable(main_test src/main_test.cpp)
ament_target_dependencies(main_test 
  ros_tensorrt_bridge
  OpenCV
  Python3
  pybind11
)

install(
  TARGETS main_test
  DESTINATION lib/${PROJECT_NAME}
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

ament_package()
