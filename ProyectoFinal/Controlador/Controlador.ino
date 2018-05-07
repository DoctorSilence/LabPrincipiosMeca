/*
Proyecto final para Principios de mecatrónica.
Controlador para seguir un camino en color blanco en un "coche"
 */

#include <SoftwareSerial.h>
#include <Servo.h>

int infraredLPin = 9;
int infraredRPin = 10;
int servoPin = 11;
int speedMonitorPin = 12;
int motorDPin = 13; // Derecho
int motorRPin = 14; // Reversa
int angle = 0;
int angleDif = 0; // Para velocidad angular
bool isOnPathL = false;
bool isOnPathR = false;
bool hasChangeSpace = false;
bool hasStarted = false;
int angleServo;
int speedMotor;
char traction;
char toMove;
Servo servoMotor;
unsigned long time;

int RX=10;
int TX=11;
int baud_rate=9600;
SoftwareSerial xbeeSerial(RX,TX);


void setup(){
  Serial.begin(9600); // Inicializamos la consola

  pinMode(infraredLPin, INPUT);
  pinMode(infraredRPin, INPUT);
  pinMode(speedMonitorPin, INPUT);
  pinMode(motorDPin, OUTPUT);
  pinMode(motorRPin, OUTPUT);

  servoMotor.attach(servoPin);

  xbeeSerial.begin(baud_rate);
}

void loop(){
  if (!hasStarted) {
    hasStarted = checkXbee();
  }
  if (hasStarted) {
    // Checamos si estamos en camino
    isOnPathL = analogRead(infraredLPin) == HIGH; // 0 a 1024
    isOnPathR = analogRead(infraredRPin) == HIGH;

    if (isOnPathL && isOnPathR) {
      speedMotor = 4;
      angleServo = 0; // Poner el servoMotor a 0º, que vaya derecho
      traction = 'd';
      toMove = 'x';
      Serial.println("Hacia el frente");
    } else if (!isOnPathL && isOnPathR) {
      speedMotor = 3;
      angleServo = 90;
      traction = 'd';
      toMove = 'r';
      Serial.println("Gira a la derecha");
    } else if (isOnPathL && !isOnPathR) {
      speedMotor = 2;
      angleServo = -90;
      traction = 'd';
      toMove = 'l';
      Serial.println("Gira a la izquierda");
    } else {
      speedMotor = 1;
      angleServo = 0; // Que se vaya derecho, lentamente
      traction = 'd';
      toMove = 'x';
      Serial.println("No encuentra linea… irá derecho más lento");
    }

    setMotor(speedMotor, traction);
    setServo(angleServo, toMove);
  }

}

void setServo(int newAngle, char moveTo) {
  if (moveTo == 'l') {
    for (int pos = angle; pos <= newAngle; pos += 1) { // 0º->180º
      servoMotor.write(pos);
      delay(15);
    }
    Serial.println("Servo: a la izquierda");
  } else if (moveTo == 'r'){
    for (int pos = angle; pos >= newAngle; pos -= 1) { // 180º->0º
      servoMotor.write(pos);
      delay(15);
    }
    Serial.println("Servo: a la derecha");
  }
  angle = newAngle;
}

void setMotor(int speed, char traction){
  // 0 a 255
  if (traction == 'd') {
    analogWrite(motorDPin, speed);
    analogWrite(motorRPin, 0);
    Serial.println("Va derecho");
  } else if (traction == 'r') {
    analogWrite(motorRPin, speed);
    analogWrite(motorDPin, 0);
  }
}

void getSpeed(int speedSensor){
  // 16 hoyos
  // 360/16
  bool isOnFreeSpace = digitalRead(speedMonitorPin) == HIGH;
  time = millis();
  if (isOnFreeSpace && hasChangeSpace) {
    Serial.println(time);
    angleDif = angleDif + 360/16;
    speedMotor = speedMotor + angleDif/time;
  }
  if (speedMotor == 0) {
    hasChangeSpace = !hasChangeSpace;
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
