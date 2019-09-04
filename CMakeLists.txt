cmake_minimum_required(VERSION 3.5)
project(crasher)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(crasher_node
  src/crasher.cpp)
ament_target_dependencies(crasher_node
  rclcpp
  sensor_msgs
)

install(TARGETS crasher_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
