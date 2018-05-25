/*
Proyecto final para Principios de mecatrónica.
Controlador para seguir un camino en color blanco en un "coche"
 */

// Servo: min - 30, max - 140

#include <SoftwareSerial.h>
#include <Servo.h>
// #include <TimerOne.h>

#include <avr/io.h>
// #include <ros.h>
// #include <std_msgs/Float64.h>

int infraredLPin = 9; // CNY70
int infraredRPin = 10; // TCRT5000
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

int cont = 0;

int vueltas = 0;
double vel = 0;
unsigned long tiempo1;
unsigned long tiempo2;

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

  // Timer1.initialize(1000000); // Timer para 1seg
  // attachInterrupt(digitalPinToInterrupt(speedMonitorPin), count, RISING);  // Aumentar contador cuando sensor está en HIGH
  // Timer1.attachInterrupt(timerIsr); // Habilitar timer
}

void loop(){
  Serial.print(digitalRead(infraredLPin));
  Serial.println(digitalRead(infraredRPin));
  //delay(500);

  tiempo2 = millis();

//  if (!hasStarted) {
//    hasStarted = checkXbee();
//  }
//  if (hasStarted) {
//    // Checamos si estamos en camino

    isOnPathL = digitalRead(infraredLPin);
    isOnPathR = digitalRead(infraredRPin);
    if (isOnPathL && isOnPathR) {
      startTime = millis();
      speedMotor = 100;
      angleServo = 90; // Poner el servoMotor a 0º, que vaya derecho
      setMotor(speedMotor, 'd');
      setServo(angleServo);
    } else if (!isOnPathL && isOnPathR) {
      
      //while (!isOnPathL && isOnPathR) {
        //tiempo2 = millis();
        newSpeedMotor = speedMotor - kp * (millis() - startTime);
        newAngleServo = angleServo + kp * (millis() - startTime);
        
        if (newSpeedMotor <= 80 || newAngleServo >= 100){
          newSpeedMotor = 80;
        }
        if (newAngleServo >= 120){
          newAngleServo = 120;
        }
        Serial.print("!L & R");
        Serial.println(newAngleServo);
        //getSpeed();
        setMotor(newSpeedMotor, 'd');
        setServo(newAngleServo);
        //isOnPathL = !digitalRead(infraredLPin) == 1;
        //isOnPathR = digitalRead(infraredRPin) == 1;
      //}
    } else if (isOnPathL && !isOnPathR) {
      
      //while (isOnPathL && !isOnPathR) {
        //tiempo2 = millis();
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
        //getSpeed();
        setMotor(newSpeedMotor, 'd');
        setServo(newAngleServo);
        //isOnPathL = !digitalRead(infraredLPin) == 1;
        //isOnPathR = digitalRead(infraredRPin) == 1;
      //}
    } else {
      startTime = millis();
      speedMotor = 80;
      angleServo = 90; // Que se vaya derecho, lentamente
      setMotor(speedMotor, 'd');
      setServo(angleServo);
    }
    
    getSpeed();
    
//  }
   // delay(100);
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
//        str_msg.data = vel;
//        chatter.publish( &str_msg );
//        nh.spinOnce();
      } else {
        vueltas = 0;
        tiempo1 = tiempo2;
        TCNT5 = 240;
      }
    }
}

void setServo(int to) {
  if (angleServo <= to) {
    for (int pos = angleServo; pos <= to; pos += 1) { // 0º->180º
      servoMotor.write(pos);
      delay(15);
    }
    //Serial.println("Servo: a la izquierda");
  } else if (to < angleServo){
    for (int pos = angleServo; pos >= to; pos -= 1) { // 180º->0º
      servoMotor.write(pos);
      delay(15);
    }
    //Serial.println("Servo: a la derecha");
  }
  angleServo = to;
}

void setMotor(int speed, char traction){
  // 0 a 255
  if (traction == 'd') {
    analogWrite(motorDPin, speed);
    analogWrite(motorRPin, 0);
    // digitalWrite(motorRPin, 1);  // set rotation of motor to Clockwise
    //Serial.println("Va derecho");
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
//  Timer1.detachInterrupt();  // Detener timer
//  Serial.print("Velocidad: ");
//  int speedMotor = (counter / 16);  // divide by number of holes in Disc
//  Serial.print(speedMotor,DEC);
//  Serial.println(" Rotación x Seg");
//  // sendSpeed(speedMotor);
//  counter=0;  //  reset counter to zero
//  Timer1.attachInterrupt( timerIsr );  // Habilitar timer
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
