/*
Proyecto final para Principios de mecatrónica.
Controlador para seguir un camino en color blanco en un "coche"
 */

// Servo: min - 30, max - 140

#include <SoftwareSerial.h>
#include <Servo.h>

#include <avr/io.h>
#include <ros.h>
#include <std_msgs/Float64.h>

int infraredLPin = 10; // CNY70
int infraredRPin = 9; // TCRT5000
int servoPin = 11;
int speedMonitorPin = 2; // Ya no mover el pin
int speedMotor = 125;
unsigned int newSpeedMotor;
unsigned int newAngleServo;
int motorDPin = 7; // Derecho
int motorRPin = 6; // Reversa
int startTime;
int angle = 0;
int angleDif = 0; // Para velocidad angular
bool isOnPathL = false;
bool isOnPathR = false;
int angleServo = 90;
float kp = 0.5;
unsigned int counter = 0;
char toMove;
Servo servoMotor;
unsigned long time;

int RX=10;
int TX=11;
int baud_rate=9600;
SoftwareSerial xbeeSerial(RX,TX);

int vueltas = 0;
float vel = 0;
unsigned long tiempo1;
unsigned long tiempo2;

float carril = 0;

ros::NodeHandle nh;
std_msgs::Float64 ve;
std_msgs::Float64 po;
ros::Publisher velo("velo", &ve);
ros::Publisher pos("pos", &po);

void setup(){
  cli();
  TCCR5B = B00001111;
  TCNT5 = 240;
  TCCR5B |= (1 << WGM01); //Esto hace que vuelva a su valor de 240
  TIMSK5 |= (1 << OCIE0A); // enable timer compare interrupt
  pinMode(47,INPUT); //PIN QUE DISPARA RUTINA DE TIMER5 de ATMEGA

  Serial.begin(9600); // Inicializamos la consola

  sei();

  pinMode(infraredLPin, INPUT);
  pinMode(infraredRPin, INPUT);
  pinMode(speedMonitorPin, INPUT);
  pinMode(motorDPin, OUTPUT);
  pinMode(motorRPin, OUTPUT);

  delay(2000);
  tiempo1 = millis();

  servoMotor.attach(servoPin);
  servoMotor.write(90); // Inicializar en 90º

  xbeeSerial.begin(baud_rate);

  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(pos);
  nh.advertise(velo);
}

void loop(){
  Serial.print(digitalRead(infraredLPin));
  Serial.println(digitalRead(infraredRPin));

  tiempo2 = millis();

//  if (!hasStarted) {
//    hasStarted = checkXbee();
//  }
//  if (hasStarted) {
//    // Checamos si estamos en camino

    isOnPathL = digitalRead(infraredLPin);
    isOnPathR = digitalRead(infraredRPin);
    if (isOnPathL && isOnPathR) {
      carril = 0;
      startTime = millis();
      speedMotor = 100;
      angleServo = 90; // Poner el servoMotor a 0º, que vaya derecho
      setMotor(speedMotor, 'd');
      setServo(angleServo);
    } else if (!isOnPathL && isOnPathR) {
      carril = -1;
      newSpeedMotor = speedMotor - kp * (millis() - startTime);
      newAngleServo = angleServo + kp * (millis() - startTime);

      if (newSpeedMotor <= 80 || newAngleServo >= 200){
        newSpeedMotor = 80;
      }
      if (newAngleServo >= 120){
        newAngleServo = 120;
      }
      Serial.print("!L & R");
      Serial.println(newAngleServo);
      setMotor(newSpeedMotor, 'd');
      setServo(newAngleServo);
    } else if (isOnPathL && !isOnPathR) {
      carril = 1;
      newSpeedMotor = speedMotor - kp * (millis() - startTime);
      newAngleServo = angleServo - kp * (millis() - startTime);

      if (newSpeedMotor <= 80 || newAngleServo >= 10.0){
        newSpeedMotor = 80;
      }
      if (newAngleServo <= 50 || newAngleServo >= 120){
        newAngleServo = 50;
      }
      Serial.print("L & !R");
      Serial.println(newAngleServo);
      setMotor(newSpeedMotor, 'd');
      setServo(newAngleServo);
    } else {
      carril = 0;
      startTime = millis();
      speedMotor = 80;
      angleServo = 90; // Que se vaya derecho, lentamente
      setMotor(speedMotor, 'd');
      setServo(angleServo);
    }

    getSpeed();

//  }
}

void getSpeed() {
  if(tiempo2-tiempo1>= 300) {
      vel = vueltas + (TCNT5-240.0)/16.0;
      if(vel>=0){
        Serial.print("La velocidad es de: ");
        Serial.print(vel); //vel*10 ??
        Serial.println(" rev/s");
        vueltas = 0;
        tiempo1 = tiempo2;
        TCNT5 = 240;

        // Aquí va lo de ROS
        sendToROS();
      } else {
        vueltas = 0;
        tiempo1 = tiempo2;
        TCNT5 = 240;
      }
    }
}

void sendToROS() {
   po.data = carril;
   ve.data = vel;
   pos.publish( &po );
   velo.publish(&ve);
   nh.spinOnce();
  // delay(10);
}

void setServo(int to) {
  if (angleServo <= to) {
    for (int pos = angleServo; pos <= to; pos += 1) { // 0º->180º
      servoMotor.write(pos);
      delay(15);
    }
  } else if (to < angleServo){
    for (int pos = angleServo; pos >= to; pos -= 1) { // 180º->0º
      servoMotor.write(pos);
      delay(15);
    }
  }
  angleServo = to;
}

void setMotor(int speed, char traction){
  // 0 a 255
  if (traction == 'd') {
    analogWrite(motorDPin, speed);
    analogWrite(motorRPin, 0);
    // digitalWrite(motorRPin, 1);  // set rotation of motor to Clockwise
  } else if (traction == 'r') {
    digitalWrite(motorRPin, speed);
    digitalWrite(motorDPin, 0);
    // digitalWrite(motorRPin, 0);  // set rotation of motor to Clockwise contrario
  }
}

bool checkXbee() {
  char letra = xbeeSerial.read();
  if (letra == 'i') { // Iniciar
    return true;
  } else if (letra == 'p') { // Parar
    return false;
  }
}

void sendSpeed(int speed) {
  xbeeSerial.write(speed);
}

ISR(TIMER5_COMPA_vect){
   vueltas++;
   //Serial.println(TCNT5);
   TCNT5 = 240;
}
