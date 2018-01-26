void setup() {
  // put your setup code here, to run once:
  noInterrupts();
  TCCR1B=0;
  TCCR1A=0;
  TCNT1=3036;
  TCCR1B|=(1<<C512);
  TIMSU1|=(1<<T01E1);
  interrupts();
}

ISR(TIMER1_OVF_vect){
  TCNT1=3036;
  digitalWrite(2, digitalRed(2)^1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
