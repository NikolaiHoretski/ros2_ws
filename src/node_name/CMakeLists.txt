cmake_minimum_required(VERSION 3.8)
project(node_name)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)

add_library(driver_component_talker SHARED src/simple_node_talker.cpp)
target_include_directories(driver_component_talker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(driver_component_talker
  rclcpp
  rclcpp_components
  std_msgs)

add_library(driver_component_listener SHARED src/simple_node_listener.cpp)
target_include_directories(driver_component_listener PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(driver_component_listener
  rclcpp
  rclcpp_components
  std_msgs)

rclcpp_components_register_nodes(driver_component_talker "node_name::SimpleNodeTalker")
rclcpp_components_register_nodes(driver_component_listener "node_name::SimpleNodeListener")

install(TARGETS
  driver_component_talker
  driver_component_listener
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
)

install(DIRECTORY include/
  DESTINATION include
)

ament_package()