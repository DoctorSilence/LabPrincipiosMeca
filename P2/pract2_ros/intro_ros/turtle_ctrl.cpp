#include <ros/ros.h>

#include <iostream>
#include <????/????.h>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"turtle_ctrl_node");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("turtle_ctrl_node initialized");																																							
	ROS_INFO_STREAM(ros::this_node::getName());

	ros::Publisher pub = nh.advertise<????::????> ("/turtle1/cmd_vel", 1);

	????::??? msg;
	int num; 
		
	while (ros::ok())
	{
		cout << "Introduce la direccion:" << endl;
		cin >> num;
		

		pub.publish(msg);
	}

    return 0;
}
