void setup() {
  // put your setup code here, to run once:
  attachInterrupt(@, button_int,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(pin,val); // Hay que hacer cambiar a VAL para que "respire", 0<=val<=255
  //...
}

void button_int(){
  bState=digitalWrite(pinBtn);
  digitalWrite(pinLED, bState);
}
