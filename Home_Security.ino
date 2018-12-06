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
char Copy_str[100];

void setup() {
  initlization(); 
   //len = strlen_P(ATIPR);
   //for(pV=0;pV<100&pV<len;pV++) uart_send(pgm_read_byte_near (ATIPR+pV));  
   
   Door_Sensor_Status(1);
   Door_Sensor_Status(2);
   print_strU0("Boot Up");
}
unsigned int loop_Message=5001;



void loop() {
     int i; res =0;
     SMS_check();
     //door_open_check();

     
     delay(1000);
     print_strU0("1");

}









