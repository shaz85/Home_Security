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
char battery_voltage = 100;


  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
void setup() {
  initlization();  
  Soft_printstr("ATE0&W\r");
}

unsigned int loop_Message=5001;

  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
static char cntv=0;
void loop() {
  int i; res =0;
  unsigned char j;
  loop_Message++;
  if(loop_Message > 2000){//uart_send('M'); 
    digitalWrite(13, HIGH); delay(200); digitalWrite(13, LOW);
    SMS_check();loop_Message =0;
    res = strstr(datastr , "$");  
    cntv++;
    if(cntv>2){
      Battery_value();
      
      cntv=0;
    }
  }    
  delay(1);
  sensors_status_check();
}



/***********************************/
void Battery_value(){
  static char battery_alert_cnt = 0, battery_alert_flag=1;
  GSM_str_clear();
  Soft_printstr("AT+CBC\r");      
  Check_RecievedSMS(1);
  //print_strU0(gsm_data);

  char *ptr;
  ptr = strstr(gsm_data, "+CBC");
  if(ptr!=0){
    ptr = strstr(gsm_data, ",");
    ptr++;
    for(char i=0;i<3; i++){
      if(*ptr == ','){Array12B[i] =0; break; }
      Array12B[i] = *ptr; ptr++;
    }
    battery_voltage = atoi(Array12B);
    print_strU0(Array12B);print_strU0(",");
    if(battery_voltage < 45){
      battery_alert_cnt++;
      if(battery_alert_cnt > 5 && battery_alert_flag ==1 ){
        Send_SMS_AlertsP2(10);

        battery_alert_flag =0;
      }

    }
    else if (battery_voltage > 75){battery_alert_cnt=0; battery_alert_flag =1;}
  }
  //+CBC: 0,97,4180


}