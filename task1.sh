#!/bin/bash

# 导入工作空间的环境变量
source devel/setup.bash

# 启动激光雷达
xterm -hold -e "roslaunch scout_bringup open_rslidar.launch" &

# 启动相机
xterm -hold -e "roslaunch realsense2_camera rs_camera.launch" &

# 启动imu 
xterm -hold -e "roslaunch imu_launch imu_msg.launch" &

# 启动 opencv 节点
xterm -hold -e "roslaunch opencv opencv.launch" &

# 启动 pcl 节点
xterm -hold -e "roslaunch pcl pcl.launch" &

# 启动 speed 节点
xterm -hold -e "roslaunch speed speed.launch" &

# 等待所有节点启动完成
wait