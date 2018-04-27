/*
Proyecto final para Principios de mecatrónica.
Controlador para seguir un camino en color blanco en un "coche"
 */

int infraredLPin = 9;
int infraredRPin = 10;
int servoPin = 11;
int oldAngle = 0;
bool isOnPathL = false;
bool isOnPathR = false;
Servo servomotor;

void setup(){
  Serial.begin(9600); // Inicializamos la consola

  pinMode(infraredLPin, INPUT); // Leemos infraredPinL
  pinMode(infraredRPin, INPUT); // Leemos infraredPinR

  servomotor.attach(servoPin);
}

void loop(){
  // Checamos si estamos en camino
  isOnPathL = digitalRead(infraredLPin) == HIGH;
  isOnPathR = digitalRead(infraredRPin) == HIGH;

  int angleServo;
  int speedMotor;
  char toMove;
  if (isOnPathL && isOnPathR) {
    speedMotor = 4;
    angleServo = 0; // Poner el servomotor a 0º, que vaya derecho
    toMove = 'x';
  } else if (!isOnPathL && isOnPathR) {
    speedMotor = 3;
    angleServo = 90;
    toMove = 'r';
  } else if (isOnPathL && !isOnPathR) {
    speedMotor = 2;
    angleServo = -90;
    toMove = 'l';
  } else {
    speedMotor = 1;
    angleServo = 0; // Que se vaya derecho, lentamente
    toMove = 'x';
  }

  setMotor(speedMotor);
  setServo(angleServo, toMove);
}

void setServo(newAngle, moveTo) {
  if (moveTo == 'l') {
    for (pos = oldAngle; pos <= newAngle; pos += 1) { // 0º->180º
      servomotor.write(pos);
      delay(15);
    }
  } else if (moveTo == 'r'){
    for (pos = oldAngle; pos >= newAngle; pos -= 1) { // 180º->0º
      servomotor.write(pos);
      delay(15);
    }
  }
  oldAngle = newAngle;
}

void setMotor(speed){

}

void getSpeed(){

}
