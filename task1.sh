#!/bin/bash

# 导入工作空间的环境变量
source devel/setup.bash

# 启动 opencv 节点
xterm -hold -e "roslaunch opencv opencv.launch" &

# 启动 pcl 节点
xterm -hold -e "roslaunch pcl pcl.launch" &

# 启动 speed 节点
xterm -hold -e "roslaunch speed speed.launch" &

# 等待所有节点启动完成
wait