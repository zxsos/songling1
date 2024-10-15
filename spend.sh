#!/bin/bash

# 导入工作空间的环境变量
source devel/setup.bash

# 启动 激光雷达
gnome-terminal -- bash -c "  roslaunch scout_bringup open_rslidar.launch ; exec bash"

# 等待几秒钟，确保 imu 节点已经启动
sleep 5

# 启动 speed 节点
gnome-terminal -- bash -c "roslaunch speed speed.launch; exec bash"