#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

ros::Publisher vel_pub;
geometry_msgs::Twist vel_msg;

using namespace std;

void desplaza(double velocidad, int dir); 

int main(int argc, char **argv){
	ros::init(argc, argv, "turtle_ctrl");
	ros::NodeHandle n;

	double velocidad = 5;
	int dir;

	vel_pub=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",5);
	while(ros::ok()){
		cin>>dir;
		desplaza(velocidad,dir);
		vel_pub.publish(vel_msg);
		ros::spinOnce();
		
	}
}

void desplaza(double velocidad, int dir){ 
	

	if(dir==6)
	{	vel_msg.linear.x=abs(velocidad);
	vel_msg.angular.z=0;
	}if(dir==4){
		vel_msg.linear.x=-abs(velocidad);
	
	vel_msg.angular.z=0;
	}
	if(dir==2)
	{	vel_msg.angular.z=abs(velocidad);
	vel_msg.linear.x=0;
	
	}
	if(dir==8)
	{	vel_msg.angular.z=-abs(velocidad);
	vel_msg.linear.x=0;
	}
	vel_msg.linear.y=0;
	vel_msg.linear.z=0;

	
	vel_msg.angular.y=0;
	vel_msg.angular.x=0;

	ros::Rate loop_rate(10);
	loop_rate.sleep();
}
