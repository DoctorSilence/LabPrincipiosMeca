void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DDRE=B00010000;
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t ans=0;

//Ve si es par o  impar e imprime la salida
//  asm volatile(
//
//    "LDI 0x16, %[IN]; \n"
//    "ANDI 0x16, 1; \n"
//    "MOV %[varA], 0x16; \n"
//    :[varA] "=r" (ans)
//    :[IN] "n" (5)
//
//  );
//
//  Serial.println(ans);


//Prender o apagar bits o leds
//  asm volatile(
//    "SBI 0x0e,4;\n" //Prende
//    "CBI 0x0e,5;\n" //Apaga
//    :
//    :
//  );

//
  asm volatile(
    "LDI %[varA], 1;\n"
    "SBI 0x0e, 4;\n"
    "SBIS %1, 5;\n"
    //"CLR %[varA];\n"
    "CBI 0x0e, 4;\n"
    :[varA] "=r" (ans)
    :"I" _SFR_IO_ADDR(PINE)
  );

  Serial.println(ans);
  
}
