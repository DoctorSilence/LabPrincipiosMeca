#include <ros.h>

ros::NodeHandle nh;
std msgs :: String str msg;
ros :: Publisher pub(”arduino msg”, &str msg );

// Declarar suscriptor
ros :: Subscriber<std msgs :: String> sub(”other msg”, &message ros );

void setup() {
  nh.initNode();
  nh.advertise(pub);

  // Inicializar suscriptor
  nh.subscribe(sub);
}

void loop() {
  // Para publicar un mensaje
  str msg.data = string variable;
  chatter.publish(&str_msg);
  nh.spinOnce();
}

// Implementar un suscriptor
void message_ros(const std_msgs::String& ros_msg){
  string_variable = ros_msg.data;
}
