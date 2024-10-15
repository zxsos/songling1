cmake_minimum_required(VERSION 3.0.2)
project(opencv)


find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  image_transport
  cv_bridge
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES opencv
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(show_camera src/show_camera.cpp)
add_dependencies(show_camera ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(show_camera
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
