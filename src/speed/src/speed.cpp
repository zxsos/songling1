// （1）a.命令行窗口显示小车的线速度和角速度

/*
开两个窗口

一个启动IMU
roslaunch imu_launch imu_msg.launch

别忘记了配置环境变量
source devel/setup.bash 

一个启动节点
rosrun speed speed_node
*/

#include <ros/ros.h> // 包含ROS的头文件，用于访问ROS的功能
#include <sensor_msgs/Imu.h> // 包含sensor_msgs包中的Imu消息类型的头文件，用于处理IMU数据

// 回调函数，当接收到IMU数据时被调用
void imuCallback(const sensor_msgs::Imu::ConstPtr& msg) {
    // 从IMU消息中提取线速度和角速度（如果可用）
    // 注意：这里提取的是线加速度而不是线速度
    geometry_msgs::Vector3 linear_velocity = msg->linear_acceleration;
    geometry_msgs::Vector3 angular_velocity = msg->angular_velocity;

    // 在ROS_INFO日志级别下打印线加速度和角速度的值
    ROS_INFO("线加速度: [%.2f, %.2f, %.2f], 角速度: [%.2f, %.2f, %.2f]",
             linear_velocity.x, linear_velocity.y, linear_velocity.z,
             angular_velocity.x, angular_velocity.y, angular_velocity.z);
}


// 主函数，程序的入口点
int main(int argc, char** argv) {
    // 初始化ROS节点，节点名为"speed_node"
    ros::init(argc, argv, "speed_node");
    ros::NodeHandle nh; // 创建一个节点句柄，用于创建订阅者、发布者等

    // 订阅名为"/IMU_data"的主题，队列大小为1000，回调函数为imuCallback
    ros::Subscriber imu_sub = nh.subscribe("/IMU_data", 1000, imuCallback);

    // 保持节点运行并处理回调函数
    ros::spin();  

    return 0; // 返回0，表示程序正常退出
}