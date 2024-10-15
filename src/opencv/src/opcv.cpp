//用OpenCV显示相机的彩色和深度图(/camera/color/image_raw、/camera/depth/image_rect_raw)

/*
开启相机
roslaunch realsense2_camera rs_camera.launch

别忘记了配置环境变量
 source devel/setup.bash

rosrun opencv show_camera

*/

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW_COLOR = "Image color window";
static const std::string OPENCV_WINDOW_DEPTH = "Image depth window";

class ImageConverter
{
  ros::NodeHandle nh_;                         // ROS节点句柄
  image_transport::ImageTransport it_;         // 图像传输对象
  image_transport::Subscriber image_sub_color; // 彩色图像订阅者
  image_transport::Subscriber image_sub_depth; // 深度图像订阅者
  image_transport::Publisher image_pub_color;  // 彩色图像发布者
  image_transport::Publisher image_pub_depth;  // 深度图像发布者

public:
  ImageConverter()
      : it_(nh_) //初始化图像传输对象
  {
    //订阅输入视频流并发布输出视频流
    image_sub_color = it_.subscribe("/camera/color/image_raw", 1, &ImageConverter::imageCb, this);
    image_sub_depth = it_.subscribe("/camera/depth/image_rect_raw", 1, &ImageConverter::depthCb, this);
    image_pub_color = it_.advertise("/camera/color/camera_info", 1);
    image_pub_depth = it_.advertise("/camera/depth/camera_info", 1);

    //创建opencv窗口
    cv::namedWindow(OPENCV_WINDOW_COLOR);
    cv::namedWindow(OPENCV_WINDOW_DEPTH);
  }

  ~ImageConverter()
  {
    // 销毁OpenCV窗口
    cv::destroyWindow(OPENCV_WINDOW_COLOR);
    cv::destroyWindow(OPENCV_WINDOW_DEPTH);
  }

  void imageCb(const sensor_msgs::ImageConstPtr &msg)
  {
    cv_bridge::CvImagePtr cv_ptr; // 创建CvImage指针
    try
    {
      // 将ROS图像消息转换为OpenCV图像格式
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception &e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    // 在视频流上绘制一个示例圆圈
    if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
      cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255, 0, 0));

    // 更新GUI窗口
    cv::imshow(OPENCV_WINDOW_COLOR, cv_ptr->image);
    cv::waitKey(3); // 等待3毫秒以处理窗口事件

    // 发布修改后的视频流
    image_pub_color.publish(cv_ptr->toImageMsg());
  }

  void depthCb(const sensor_msgs::ImageConstPtr &msg)
  {
    cv_bridge::CvImagePtr cv_ptr; // 创建CvImage指针
    try
    {
      // 将ROS深度图像消息转换为OpenCV图像格式
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_32FC1);
    }
    catch (cv_bridge::Exception &e)
    {
      ROS_ERROR("cv_bridge异常: %s", e.what()); // 报错信息
      return;
    }

    // 在深度图像上绘制一个示例圆圈
    if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
      cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255, 0, 0));

    // 更新GUI窗口
    cv::imshow(OPENCV_WINDOW_DEPTH, cv_ptr->image);
    cv::waitKey(3); // 等待3毫秒以处理窗口事件

    // 发布修改后的深度图像
    image_pub_depth.publish(cv_ptr->toImageMsg());
  }
};

int main(int argc, char **argv)
{
  // 初始化ROS节点
  ros::init(argc, argv, "show_camera");
  ImageConverter ic; // 创建ImageConverter对象
  ros::spin();       // 进入事件循环
  return 0;
}