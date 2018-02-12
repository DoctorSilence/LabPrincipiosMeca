#include <ros.h>

ros::NodeHandle nh;
std msgs :: String str msg;
ros :: Publisher pub(”arduino msg”, &str msg );

void setup() {
  nh.initNode();
  nh.advertise(pub);
}

void loop() {
  str msg.data = string variable;
  chatter.publish(&str_msg);
  nh.spinOnce();
}
