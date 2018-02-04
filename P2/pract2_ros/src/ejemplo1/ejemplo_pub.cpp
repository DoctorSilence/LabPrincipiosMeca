#include <ros/ros.h>

#include <iostream>
#include <std_msgs/Int32.h>
using namespace std;
	int num; 

void get_mesg(const std_msgs::Int32& mesg) {
	num = mesg.data;
	ROS_INFO_STREAM("Valor recibido: " << num);
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"ejemplo_pub_node");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("ejemplo_pub_node initialized");																																							
	ROS_INFO_STREAM(ros::this_node::getName());

	ros::Publisher pub = nh.advertise<std_msgs::Int32> ("/msg_ejemplo", 1);
	ros::Subscriber sub_vel = nh.subscribe("/msg_rec", 1000, &get_mesg);

	std_msgs::Int32 msg;

		
	while (ros::ok())
	{



		cout << "Introduce un numero entero:" << endl;
		cin >> num;
		if(num=!0){
		msg.data = num;
		pub.publish(msg);
		}

		ROS_INFO_STREAM(&get_mesg);
	}

    return 0;
}
