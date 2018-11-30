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
}
unsigned int loop_Message=5001;
void loop() {
     int i; res =0;
     unsigned char j;
     loop_Message++;
     if(loop_Message > 5000){uart_send('M'); 
       digitalWrite(13, HIGH); delay(200); digitalWrite(13, LOW);SMS_check();loop_Message =0;
      res = strstr(datastr , "$"); 
      uart_send(Zone1_Prev);uart_send(','); uart_send(Zone2_Prev);uart_send(',');
      uart_send(Zone3_Prev);uart_send(','); uart_send(Zone4_Prev);uart_send(',');
      uart_send(Zone5_Prev);uart_send(',');
      //if(res !=0)print_strU0("Shahzad");
     }
       
       if(dat_cnt>90 | datastr[dat_cnt-1] =='$' | res !=0){
         j=0; strcpy( Copy_str, datastr);
         dat_cnt=0;   for(i=0;i<100;i++)datastr[i]=0;         
          
         for(i=0;Copy_str[i]!=0 && i < 100;i++){
            if (Copy_str [i] == '$')j++;
         }       
         // print_strU0(Copy_str);  
         Door_Alert_opt(j);
           
       }
     
     delay(1);

}





void Door_Alert_opt(unsigned char NoPacket){
  unsigned char i,j;
    if(NoPacket == 1){
       for(i=0;i<100 && Copy_str[i]!=0; i++) if(Copy_str[i]==','){i++;break;}
      if(strstr(Copy_str ,"%1")!=0)Home_S_sensorsSt (one, Copy_str[i]); 
      else if(strstr(Copy_str ,"%2")!=0)Home_S_sensorsSt (two, Copy_str[i]); 
      else if(strstr(Copy_str ,"%3")!=0)Home_S_sensorsSt (three, Copy_str[i]); 
      else if(strstr(Copy_str ,"%4")!=0)Home_S_sensorsSt (four, Copy_str[i]); 
      else if(strstr(Copy_str ,"%5")!=0)Home_S_sensorsSt (five, Copy_str[i]); 
      else if(strstr(Copy_str ,"%6")!=0)Home_S_sensorsSt (six, Copy_str[i]); 
      else if(strstr(Copy_str ,"%7")!=0)Home_S_sensorsSt (seven, Copy_str[i]); 
      else if(strstr(Copy_str ,"%8")!=0)Home_S_sensorsSt (eight, Copy_str[i]); 
      else if(strstr(Copy_str ,"%9")!=0)Home_S_sensorsSt (nine, Copy_str[i]); 
      
      Motion_and_Smoke(); 
    }
    
    if(NoPacket > 1){i=0;
      strcpy(gsm_data ,Copy_str);
      for(j=0;j<NoPacket;j++){ 
          if(j>0){strcpy(Copy_str , res = strstr(gsm_data, "$\r") ); strcpy(gsm_data , res = strstr(Copy_str, "\r") );}
          for(;i<100 && Copy_str[i]!=0; i++) if(Copy_str[i]==','){i++;break;}
          if(strstr(Copy_str ,"%1")!=0)Home_S_sensorsSt (one, Copy_str[i]); 
          else if(strstr(Copy_str ,"%2")!=0)Home_S_sensorsSt (two, Copy_str[i]); 
          else if(strstr(Copy_str ,"%3")!=0)Home_S_sensorsSt (three, Copy_str[i]); 
          else if(strstr(Copy_str ,"%4")!=0)Home_S_sensorsSt (four, Copy_str[i]); 
          else if(strstr(Copy_str ,"%5")!=0)Home_S_sensorsSt (five, Copy_str[i]); 
          else if(strstr(Copy_str ,"%6")!=0)Home_S_sensorsSt (six, Copy_str[i]); 
          else if(strstr(Copy_str ,"%7")!=0)Home_S_sensorsSt (seven, Copy_str[i]); 
          else if(strstr(Copy_str ,"%8")!=0)Home_S_sensorsSt (eight, Copy_str[i]); 
          else if(strstr(Copy_str ,"%9")!=0)Home_S_sensorsSt (nine, Copy_str[i]); 
          uart_send('%');
          Motion_and_Smoke(); 
      }
    }
    
    


}





