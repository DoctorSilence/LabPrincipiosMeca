#include <Wire.h>

int X=8;

int LED1=5;
int LED2=6;
int LED3=7;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(X);
  Wire.onReceive(receiveFunction);
  Wire.onRequest(requestFunction);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveFunction(int numBytes){
  while(1<Wire.available()){
    int rec=Wire.read();

    if(rec==1)
      digitalWrite(LED1, HIGH);
    if(rec==2)
      digitalWrite(LED2, HIGH);
    if(rec==3)
      digitalWrite(LED3, HIGH);
  }
  
}

void requestFunction(){
  byte res=1;
  Wire.write(res);
}

