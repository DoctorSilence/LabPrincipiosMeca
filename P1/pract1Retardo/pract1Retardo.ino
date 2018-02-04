void setup() {
  Serial.begin(9600);
   DDRE=B11111111;
}

void loop() {

  
  asm volatile(
    "LED_Main: \n"
      "SBI 0x0e,4; \n"
      "LDI r16, 0XFF; \n"
      "LDI r17, 0xFF; \n"
      "LDI r18, 0xFF; \n"
      "rcall LED_LOOP; \n"
      "CBI 0x0e, 4; \n"
      "LDI r16, 0xFF; \n"
      "LDI r17, 0xFF; \n"
      "LDI r18, 0xFF; \n"
      "rcall LED_LOOP \n"
      "rJMP LED_Main \n"

      "LED_LOOP: \n"
        "LED_LOOP2: \n"
          "LED_LOOP3: \n"
            "DEC r16; \n"
            "BRNE LED_LOOP3; \n"
          "DEC r17; \n"
        "BRNE LED_LOOP2; \n"
      "DEC r18; \n"
      "BRNE LED_LOOP; \n"
      "RET\n"     
      :     
      :
  );

}
