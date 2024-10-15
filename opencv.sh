#!/bin/bash

# 导入工作空间的环境变量
source devel/setup.bash

# 在新的终端窗口中启动相机
gnome-terminal -- bash -c "roslaunch realsense2_camera rs_camera.launch; exec bash"

# 等待几秒钟，确保第一个节点已经启动
sleep 5

# 在另一个新的终端窗口中启动 opencv 节点
gnome-terminal -- bash -c "roslaunch opencv opencv.launch; exec bash"