#!/bin/bash

# 导入工作空间的环境变量
source devel/setup.bash

# 启动相机
konsole -e bash -c "roslaunch realsense2_camera rs_camera.launch; exec bash" &

# 启动 opencv 节点
konsole -e bash -c "roslaunch opencv opencv.launch; exec bash" &
sleep 1

# 启动激光雷达
konsole -e bash -c "roslaunch scout_bringup open_rslidar.launch; exec bash" &

# 启动 pcl 节点
konsole -e bash -c "roslaunch pcl pcl.launch; exec bash" &

sleep 1

konsole -e bash -c "  roslaunch scout_bringup open_rslidar.launch ; exec bash" &

# 启动 speed 节点
konsole -e bash -c "roslaunch speed speed.launch; exec bash" &

# 等待所有节点启动完成
wait