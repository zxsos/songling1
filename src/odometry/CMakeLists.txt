cmake_minimum_required(VERSION 3.0.2)
project(odometry)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  nav_msgs
)

catkin_package(
  # INCLUDE_DIRS include
  LIBRARIES odometry
  CATKIN_DEPENDS roscpp rospy std_msgs
  # DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(odometry src/odometry.cpp)
add_dependencies(odometry ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(odometry
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)
