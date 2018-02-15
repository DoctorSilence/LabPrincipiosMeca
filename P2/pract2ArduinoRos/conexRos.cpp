#include <ros/ros.h>

#include <iostream>
#include <std_msgs/Int32.h>
using namespace std;

void get_mesg(const std_msgs::Int32& mesg) {
	str = mesg.data;
	ROS_INFO_STREAM("Valor recibido: " << str);
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"ejemplo_pub_node");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("ejemplo_pub_node initialized");

	ros::Publisher pub = nh.advertise<std_msgs::Int32> ("/msgArduino", 1);
	ros::Subscriber sub_vel = nh.subscribe("/msgFromArduino", 1000, &get_msg);

	std_msgs::Int32 msg;
	int num;

	while (ros::ok())
	{

		cout << "Introduce un numero entero:" << endl;
		cin >> num;

		msg.data = num;
		pub.publish(msg);

		ROS_INFO_STREAM(ros::this_node::getName());
	}

    return 0;
}
