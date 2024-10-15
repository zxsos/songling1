cmake_minimum_required(VERSION 3.0.2)
project(pcl)

find_package(PCL REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  pcl_ros
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pcl
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(show_pcl_node src/show_pcl_node.cpp)
add_dependencies(show_pcl_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(show_pcl_node
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)
