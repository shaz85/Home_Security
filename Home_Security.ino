#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "Main1H.h"
#include "MainH.h"
SoftwareSerial mySerial(10, 11); // RX, TX
char not_send_newline_flag = 0;
long int reboot_value_cnt=0;
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
char bv_str[] ="AT+CBC\r";
char sq_str[] ="AT+CSQ\r";
volatile unsigned char counter = 48; 
volatile unsigned char result = 0; 
void(* resetFunc) (void) = 0; //declare reset function @ address 0 //New code 29/5/15
//char Copy_str[100];
unsigned int battery_voltage = 100;
char device_verison[]= "RMS V1.0 Build Time:";


  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
long next_idle_ms = millis();
void setup() {
  initlization();  
  Soft_printstr("ATE0&W\r");
  next_idle_ms = millis();
  UART0_NL();
  print_strU0(device_verison);
  print_strU0(__TIME__);print_strU0(" Date:");print_strU0(__DATE__);
  UART0_NL();
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
  if(loop_Message > 3000){//uart_send('M'); 
    digitalWrite(13, HIGH); 
    
  
    SMS_check();  loop_Message =0;     
    cntv++;       digitalWrite(13, LOW);
    if(cntv>2){
      Battery_value();      
      cntv=0;
    }

    itoa(millis()- next_idle_ms , Array12B,10);
    //print_strU0(Array12B);  
  }    
  delay(1);   
  sensors_status_check();
  reboot_value_cnt =0;

}



/***********************************/
void Battery_value(){
  static char battery_alert_cnt = 0, battery_alert_flag=1;
  if(Sensor_8E == 0x31){
    GSM_str_clear();
    Soft_printstr(bv_str);      
    Check_RecievedSMS(1);
    if(strlen(gsm_data)<5)mySerial.begin(9600);
    //print_strU0(gsm_data);

    char *ptr;
    for(char i=0;i<12; i++){Array12B[i] =0; }

    ptr = strstr(gsm_data, "+CBC");
    if(ptr!=0){
      ptr = strstr(gsm_data, ",");
      for(char i=0; i <100 && gsm_data[i]!=0;i++){
        if(gsm_data[i]!=10 && gsm_data[i] != 13)
          uart_send(gsm_data[i]);
        else uart_send(' ');
      }
      
      ptr++;
      for(char i=0;i<3; i++){
        if(*ptr == ','){Array12B[i] =0; break; }
        Array12B[i] = *ptr; ptr++;
      }
      battery_voltage = atoi(Array12B);
      print_strU0("BV=");
      print_strU0(Array12B);print_strU0(",");

      if(battery_voltage < 60){
        battery_alert_cnt++;
        if(battery_alert_cnt > 4 && battery_alert_flag ==1 ){
          Send_SMS_AlertsP2(10);
          battery_alert_flag =0;
          print_strU0("Alert battery Low");
        }
      }
      else if (battery_voltage > 75){battery_alert_cnt=0; battery_alert_flag =1;}
      UART0_NL();
    }
    //+CBC: 0,97,4180
  }


}