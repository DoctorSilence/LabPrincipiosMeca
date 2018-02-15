#include <ros.h>

ros::NodeHandle nh;
std msgs :: String str_msg;
ros :: Publisher pub("/msgFromArduino", &str_msg );

// Declarar suscriptor
ros :: Subscriber<std_msgs :: String> sub("/msgArduino", &message_ros );

// LED: Puerto
int LED = 2;

void setup() {
  nh.initNode();
  nh.advertise(pub);

  // Inicializar suscriptor
  nh.subscribe(sub);

  // LED
  pinMode(LED, OUTPUT);
}

void loop() {
  // Para publicar un mensaje
  //str_msg.data = string_variable;
  //chatter.publish(&str_msg);
  
  nh.spinOnce();
}

// Implementar un suscriptor
void message_ros(const std_msgs::String& ros_msg){
  ledStatus(1);
  delay(3000); // espera por 3 seg
  string_variable = ros_msg.data; // EG: Como obtener contenido de ros_msg
  // Inicia el mensaje de regreso
  str_msg.data = "Listo";
  chatter.publish(&str_msg);
}

// Prender o apagar un LED, con una sintaxis más sencilla
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
