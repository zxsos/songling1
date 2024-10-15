// PCL显示激光雷达的点云数据（/velodyne_points）

/*

先开启激光雷达数据  roslaunch scout_bringup open_rslidar.launch

配置环境变量 source devel/setup.bash 

运行节点 rosrun pcl show_pcl_node
*/

#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <string.h>

#include <pcl/io/pcd_io.h>  // PCL库用于输入输出PCD文件
#include <pcl/io/io.h>      // PCL库基本输入输出功能
#include <pcl/point_types.h> // 定义点云的数据类型
#include <pcl/point_cloud.h> // 定义点云结构
#include <pcl/visualization/pcl_visualizer.h> // PCL可视化工具
// #include <pcl/point_types.h>
// #include <pcl/filters/statistical_outlier_removal.h>   //统计滤波
// #include <pcl/filters/random_sample.h>    //随机采样
// #include <pcl/filters/voxel_grid.h>      //体素滤波
// #include <pcl/filters/passthrough.h>     //直通滤波


#include <boost/thread/thread.hpp>// PCL和ROS消息转换
 
#include <pcl_conversions/pcl_conversions.h>
using namespace std;

// 创建PCL可视化对象
boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer1(new pcl::visualization::PCLVisualizer("实时点云可视化"));

ros::Publisher pub; // 声明ROS发布者

// 定义点云类型
typedef pcl::PointCloud<pcl::PointXYZ> PointCloud; 

// 点云回调函数
void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
   // 声明存储原始数据与滤波后的数据的点云的格式
   pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; // 原始的点云数据格式
   pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
   
   // 将ROS的点云消息转换为PCL格式
   pcl_conversions::toPCL(*input, *cloud);
   pub.publish(*cloud); // 发布点云数据

   // 创建点云对象并将ROS消息转换为PCL点云格式
   pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1;
   cloud1.reset(new pcl::PointCloud<pcl::PointXYZ>);
   pcl::fromROSMsg(*input, *cloud1);

   // 移除当前所有点云
   viewer1->removeAllPointClouds();  
   // 添加新的点云数据到可视化窗口
   viewer1->addPointCloud(cloud1, "实时点云");
   viewer1->updatePointCloud(cloud1, "实时点云"); // 更新可视化窗口
   viewer1->spinOnce(0.001); // 处理可视化窗口事件
}

int main (int argc, char** argv)
{
  // 初始化ROS节点
  ros::init(argc, argv, "show_pcl_node");
  ros::NodeHandle nh;

  // 创建一个ROS订阅者，用于订阅点云数据
  ros::Subscriber sub = nh.subscribe("/rslidar_points", 10, cloud_cb);
  
  // 创建一个ROS发布者，用于发布点云数据
  pub = nh.advertise<pcl::PCLPointCloud2>("output", 10);
  
  // 进入ROS事件循环
  ros::spin();
}