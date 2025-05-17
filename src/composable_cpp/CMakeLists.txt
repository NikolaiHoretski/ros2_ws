cmake_minimum_required(VERSION 3.8)
project(composable_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
  include
)

add_library(vincent_driver_component SHARED src/vincent_driver.cpp)

ament_target_dependencies(vincent_driver_component
rclcpp
rclcpp_components
std_msgs
)

rclcpp_components_register_nodes(
  vincent_driver_component
  PLUGIN "palomino::VincentDriver"
  EXECUTABLE vincent_driver
)

ament_export_targets(export_vincent_driver_component)

install(TARGETS vincent_driver_component
EXPORT  export_vincent_driver_component
ARCHIVE DESTINATION lib
LIBRARY DESTINATION lib
RUNTIME DESTINATION lib
)

ament_package()
