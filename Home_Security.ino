#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "Main1H.h"
#include "MainH.h"
SoftwareSerial mySerial(10, 11); // RX, TX
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

volatile unsigned char counter = 48; 
volatile unsigned char result = 0; 
void(* resetFunc) (void) = 0; //declare reset function @ address 0 //New code 29/5/15
//char Copy_str[100];

  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
void setup() {
  initlization();  
}

unsigned int loop_Message=5001;

  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
void loop() {
  int i; res =0;
  unsigned char j;
  loop_Message++;
  if(loop_Message > 3000){uart_send('M'); 
    digitalWrite(13, HIGH); delay(200); digitalWrite(13, LOW);
    SMS_check();loop_Message =0;
    res = strstr(datastr , "$");      
  }    
  delay(1);
  sensors_status_check();
}
