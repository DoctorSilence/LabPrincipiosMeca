#include <ros.h>

ros::NodeHandle nh;
std msgs :: String str msg;
ros :: Publisher pub("/msgFromArduino", &str msg );

// Declarar suscriptor
ros :: Subscriber<std msgs :: String> sub("/msgArduino", &message ros );

// LED
int pinButton = 8;
int LED = 2;

void setup() {
  nh.initNode();
  nh.advertise(pub);

  // Inicializar suscriptor
  nh.subscribe(sub);

  // LED
  pinMode(pinButton, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // Para publicar un mensaje
  ledStatus(1);
  str msg.data = string variable;
  chatter.publish(&str_msg);
  nh.spinOnce();
  ledStatus(0)
}

// Implementar un suscriptor
void message_ros(const std_msgs::String& ros_msg){
  string_variable = ros_msg.data;
}

// 0 - Apagado
// 1 - Prendido
void ledStatus(int status){
  if (status) {
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
