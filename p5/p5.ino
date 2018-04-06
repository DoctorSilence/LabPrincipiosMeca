/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

String posD="";

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("\n\nString toInt():");
  Serial.println();
}

void loop() {
//  int posD, t;

  if (Serial.available() > 0) {
    Serial.print("Ingresa pos:");
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      posD += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '!') {
      Serial.print("Value:");
      Serial.println(posD.toInt());
      // clear the string for new input:
      posD = "";
    }
//    posD = (int) Serial.read();
//    Serial.println(posD);
//    t = 10;
//    Serial.print("Ingresa t:");
//    t=Serial.read();
//    Serial.println(t);
//    loadServo(posD, t);
  }


//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(5);                       // waits 15ms for the servo to reach the position
//  }
  
}

void loadServo(int posD, int t){
    for (pos = 0; pos <= posD; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    
    delay(t);                       // waits 15ms for the servo to reach the position
  }
}

//#include <Servo.h>
//Servo servo1;
//Servo servo2;
//Servo servo3;
//void setup() 
//{ 
// servo1.attach(9);
//// servo3.attach(5, 1000, 2000);
// 
// //servo1.write(90); // set servo to mid-point (90°)
// servo1.writeMicroseconds(4000);
// //servo3.write(90); // set servo to mid-point (90°)
//} 
//void loop() {}
