#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

using namespace std;
using namespace cv;

class CannyEdge
{
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_;
	image_transport::Publisher image_pub_;
	
	public:
	CannyEdge()
		: it_(nh_)
	{
		image_sub_ = it_.subscribe("/cv_camera/image_raw", 1,&CannyEdge::cannyCallBack, this);
		image_pub_ = it_.advertise("/canny_edge/canny_image", 1);
	} 
	
	void cannyCallBack(const sensor_msgs::ImageConstPtr& msg)
	{
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		}
		catch (cv_bridge::Exception& e)
		{
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}
		int lowThreshold = 50;
		int ratio = 3;
		int kernel_size = 3;
		
		Mat canny_image;
		Canny(cv_ptr->image, canny_image,lowThreshold, lowThreshold*ratio, kernel_size);
		
		
		try
		{
			cv_bridge::CvImage image_bridge = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::MONO8, canny_image);			        
			sensor_msgs::Image msg;
			image_bridge.toImageMsg(msg);
			image_pub_.publish(msg);
		}
		catch (cv_bridge::Exception& e)
                {
                        ROS_ERROR("cv_bridge exception: %s", e.what());
                        return;
                }

	}
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "canny_edge_my_face");
	CannyEdge ce;
	ros::spin();
	return 0;
}


