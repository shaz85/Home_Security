#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "Main1H.h"
#include "MainH.h"
SoftwareSerial mySerial(10, 11); // RX, TX
//#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
//#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

String text; 
String sender_number;
char text_message[150];
char number[15];

volatile unsigned char counter = 48; 
volatile unsigned char result = 0; 
void(* resetFunc) (void) = 0; //declare reset function @ address 0 //New code 29/5/15
char Copy_str[100];
#include <Sim800l.h>
Sim800l Sim800l;

void setup() {
  initlization(); 
   //len = strlen_P(ATIPR);
   //for(pV=0;pV<100&pV<len;pV++) uart_send(pgm_read_byte_near (ATIPR+pV)); 
  Serial.begin(9600);
  Sim800l.begin(); // initializate the library. 
  print_strU0("Boot Up");
  Serial.println(Sim800l.message_storage_place()); 
}
unsigned int loop_Message=5001;

unsigned int led_tog_cnt=0, cnt=0;

void loop() {
  static unsigned int i, togglecnt=0; 
  res =0;
  if(i==200){
    SMS_check();i=0;
    
    if(digitalRead(ZONE1_PIN))print_strU0("1 ");    
    else print_strU0("0 ");

    if(digitalRead(ZONE2_PIN))print_strU0("1 ");    
    else print_strU0("0 ");

    if(digitalRead(ZONE3_PIN))print_strU0("1 ");    
    else print_strU0("0 ");

    if(digitalRead(ZONE4_PIN))print_strU0("1 ");    
    else print_strU0("0 ");
    print_strU0("  \r");
  }
  sensors_status_check();
if(togglecnt>100){
  digitalWrite(13, digitalRead(13) ^ 1);   // toggle LED pin
  togglecnt=0;
}
i++;
togglecnt++;
 
  delay(10);
  

}









