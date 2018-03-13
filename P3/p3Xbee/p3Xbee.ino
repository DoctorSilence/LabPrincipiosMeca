#include <SoftwareSerial.h>

int RX=10;
int TX=11;
int baud_rate=9600;
int num=45;
int LED=8;
int LED1=7;
int LED2=6;
int BUTTON=5;
SoftwareSerial xbee_serial(RX,TX);

void setup() {
  // put your setup code here, to run once:
  xbee_serial.begin(baud_rate);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //PARA ESCRIBIR
  //xbee_serial.write(num);
  //Serial.println(num);

  //PARA LEER de XBee
  char c = xbee_serial.read();
  Serial.println(c);
  if(c=='a'){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
  if(c=='b'){
    digitalWrite(LED1, HIGH);
  }
  else{
    digitalWrite(LED1, LOW);
  }
  if(c=='c'){
    digitalWrite(LED2, HIGH);
  }
  else{
    digitalWrite(LED2, LOW);
  }

  //LEER BOTON
  int buttonState = digitalRead(BUTTON);
  if(buttonState==HIGH){
    xbee_serial.write(num);
  }
}
