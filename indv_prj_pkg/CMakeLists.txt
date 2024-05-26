cmake_minimum_required(VERSION 3.8)
project(indv_prj_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(interfaces_indv_prj_pkg REQUIRED)                      # CHANGE

add_executable(drone_thruster_pub src/drone_thruster_pub.cpp)
ament_target_dependencies(drone_thruster_pub rclcpp interfaces_indv_prj_pkg)    # CHANGE


install(TARGETS
drone_thruster_pub
  DESTINATION lib/${PROJECT_NAME})

ament_package()
