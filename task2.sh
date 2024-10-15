#!/bin/bash

# 导入工作空间的环境变量
source devel/setup.bash

# 启动 odometry 节点
roslaunch odometry odometry.launch