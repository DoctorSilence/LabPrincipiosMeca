#include <Wire.h>
#include <SoftwareSerial.h>

int X=8;
int N=1;

int RX=10;
int TX=11;

int baud_rate=9600;

byte envio;

SoftwareSerial xbee_serial(RX,TX);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  xbee_serial.begin(baud_rate);
}

void loop() {
  // put your main code here, to run repeatedly:
  char letra = xbee_serial.read();

  // Mandar del maistro al esclavo
  if(letra=='a' || letra=='b' || letra=='c'){
    Wire.beginTransmission(X);
  
    if(letra=='a'){
      envio=97;
    }
    else if(letra=='b'){
      envio=98;
    }
    else if(letra=='c'){
      envio=99;
    }
  
    Wire.write(envio);
    Wire.endTransmission();
  }

  // Para leer del esclavo
  Wire.requestFrom(X,N);

  while (Wire.available()) {
    char res = Wire.read();
    if(res!=)
    xbee_serial.write(res);
  }
  
}
