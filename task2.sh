#!/bin/bash

# 导入工作空间的环境变量
source devel/setup.bash

# 启动激光雷达
xterm -hold -e "roslaunch scout_bringup open_rslidar.launch" &

# 启动 odometry 节点
roslaunch odometry odometry.launch