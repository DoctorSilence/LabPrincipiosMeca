/*
Proyecto final para Principios de mecatrónica.
Controlador para seguir un camino en color blanco en un "coche"
 */

// Servo: min - 10, max - 170

#include <SoftwareSerial.h>
#include <Servo.h>
#include <TimerOne.h>

int infraredLPin = 9; // CNY70
int infraredRPin = 10; // TCRT5000
int servoPin = 11;
int speedMonitorPin = 2; // Ya no mover el pin
int speedMotor = 125;
int newSpeedMotor;
int newAngleServo;
int motorDPin = 13; // Derecho
int motorRPin = 14; // Reversa
int startTime;
int angle = 0;
int angleDif = 0; // Para velocidad angular
bool isOnPathL = false;
bool isOnPathR = false;
int angleServo = 90;
float kp = 0.1;
unsigned int counter = 0;
char toMove;
Servo servoMotor;
unsigned long time;

int RX=10;
int TX=11;
int baud_rate=9600;
SoftwareSerial xbeeSerial(RX,TX);

int cont = 0;

void setup(){
  Serial.begin(9600); // Inicializamos la consola

  pinMode(infraredLPin, INPUT);
  pinMode(infraredRPin, INPUT);
  pinMode(speedMonitorPin, INPUT);
  pinMode(motorDPin, OUTPUT);
  pinMode(motorRPin, OUTPUT);

  servoMotor.attach(servoPin);
  servoMotor.write(90); // Inicializar en 90º

  xbeeSerial.begin(baud_rate);

  Timer1.initialize(1000000); // Timer para 1seg
  attachInterrupt(digitalPinToInterrupt(speedMonitorPin), count, RISING);  // Aumentar contador cuando sensor está en HIGH
  Timer1.attachInterrupt(timerIsr); // Habilitar timer
}

void loop(){

//  if (!hasStarted) {
//    hasStarted = checkXbee();
//  }
//  if (hasStarted) {
//    // Checamos si estamos en camino

    isOnPathL = !digitalRead(infraredLPin) == 1;
    isOnPathR = digitalRead(infraredRPin) == 1;
    if (isOnPathL && isOnPathR) {
      speedMotor = 150;
      angleServo = 90; // Poner el servoMotor a 0º, que vaya derecho
      setMotor(speedMotor, 'd');
      setServo(angleServo);
      Serial.println("Hacia el frente");
    } else if (!isOnPathL && isOnPathR) {
      startTime = millis();
      // angleServo = 45;
      // speedMotor = 50;
      while (!isOnPathL && isOnPathR) {
        newSpeedMotor = speedMotor - kp * (millis() - startTime);
        newAngleServo = angleServo + kp * (millis() - startTime);
        if (newSpeedMotor <= 80){
          newSpeedMotor = 80;
        }
        if (newAngleServo >= 160){
          newAngleServo = 160;
        }
        setMotor(newSpeedMotor, 'd');
        setServo(newAngleServo);
        isOnPathL = !digitalRead(infraredLPin) == 1;
        isOnPathR = digitalRead(infraredRPin) == 1;
        Serial.println("Gira a la derecha"); 
      }
    } else if (isOnPathL && !isOnPathR) {
      startTime = millis();
      // angleServo = 135;
      // speedMotor = 50;
      while (isOnPathL && !isOnPathR) {
        newSpeedMotor = speedMotor - kp * (millis() - startTime);
        newAngleServo = angleServo - kp * (millis() - startTime);
        if (newSpeedMotor <= 80){
          newSpeedMotor = 80;
        }
        if (newAngleServo <= 20){
          newAngleServo = 20;
        }
        setMotor(newSpeedMotor, 'd');
        setServo(newAngleServo);
        isOnPathL = !digitalRead(infraredLPin) == 1;
        isOnPathR = digitalRead(infraredRPin) == 1;
        Serial.println("Gira a la izquierda"); 
      }
    } else {
      speedMotor = 80;
      angleServo = 90; // Que se vaya derecho, lentamente
      setMotor(speedMotor, 'd');
      setServo(angleServo);
      Serial.println("No encuentra linea... irá derecho más lento");
    }
//  }
  delay(200);
}

void setServo(int to) {
  if (angleServo <= to) {
    for (int pos = angleServo; pos <= to; pos += 1) { // 0º->180º
      servoMotor.write(pos);
      delay(15);
    }
    Serial.println("Servo: a la izquierda");
  } else if (to < angleServo){
    for (int pos = angleServo; pos >= to; pos -= 1) { // 180º->0º
      servoMotor.write(pos);
      delay(15);
    }
    Serial.println("Servo: a la derecha");
  }
  angleServo = to;
}

void setMotor(int speed, char traction){
  // 0 a 255
  if (traction == 'd') {
    analogWrite(motorDPin, speed);
    analogWrite(motorRPin, 0);
    // digitalWrite(motorRPin, 1);  // set rotation of motor to Clockwise
    Serial.println("Va derecho");
  } else if (traction == 'r') {
    digitalWrite(motorRPin, speed);
    digitalWrite(motorDPin, 0);
    // digitalWrite(motorRPin, 0);  // set rotation of motor to Clockwise contrario
  }
}

void getSpeed(int speedSensor){
  // 16 hoyos
  // 360/16

}

void count() {  // counts from the speed sensor
  counter++;  // increase +1 the counter value
}

void timerIsr() {
  Timer1.detachInterrupt();  // Detener timer
  Serial.print("Velocidad: ");
  int speedMotor = (counter / 16);  // divide by number of holes in Disc
  Serial.print(speedMotor,DEC);
  Serial.println(" Rotación x Seg");
  sendSpeed(speedMotor);
  counter=0;  //  reset counter to zero
  Timer1.attachInterrupt( timerIsr );  // Habilitar timer
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
