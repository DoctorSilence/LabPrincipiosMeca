#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;
std_msgs::Int32 str_msg;
ros :: Publisher pub("/msgFromArduino", &str_msg );

// LED: Puerto
int LED = 5;

// Implementar un suscriptor
void message_ros(const std_msgs::Int32& ros_msg){
 
  digitalWrite(LED, HIGH);
  delay(3000); // espera por 3 seg
 int string_variable = ros_msg.data; // EG: Como obtener contenido de ros_msg
  // Inicia el mensaje de regreso
  str_msg.data = 1;
  pub.publish(&str_msg);
}


// Declarar suscriptor

ros :: Subscriber<std_msgs :: Int32> sub("/msgArduino", &message_ros );

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

