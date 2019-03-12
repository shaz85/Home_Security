
void initlization(void){
   
  
  sbi(UCSR0A, U2X0);   sbi(UCSR0B, RXCIE0);    sbi(UCSR0B, RXEN0); 
  sbi(UCSR0B, TXEN0);  UCSR0C = B00000110;     UBRR0H = B0;   UBRR0L = 207;
  
  cli();
  // sbi(UCSR0A, U2X0);   sbi(UCSR0B, RXCIE0);    sbi(UCSR0B, RXEN0); 
  // sbi(UCSR0B, TXEN0);  UCSR0C = B00000110;    UBRR0H = 0x06; //UBRR0H = B0;   
  // UBRR0L = 0x82; //1200 Baud rate
   //set timer1 interrupt at 1Hz
  /*TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 60;// = (16*10^6) / (1*1024) - 1 (must be <65536) // old 15624 for 1sec
  // turn on CTC mode
  TCCR1B |= (1 << WGM01); // old (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS01) | (1 << CS00);  //old (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  */

  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  OCR2A = 124 *2;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR2B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  pinMode(GSM_Reboot_Pin,OUTPUT);   digitalWrite(GSM_Reboot_Pin, HIGH);//delay(10000);
  pinMode(3,OUTPUT);

  pinMode(ZONE1_PIN,INPUT);
  pinMode(ZONE2_PIN,INPUT);
  pinMode(ZONE3_PIN,INPUT);
  pinMode(ZONE4_PIN,INPUT);
  mySerial.begin(9600);
  pinMode(13, OUTPUT);
  cli();
  New_Setting();

  sei();

}


  //**************************************************************//
 //************************ New_Setting  ************************//
//**************************************************************//

void New_Setting(void){
     
  int i;
  unsigned char Plus = '+',Minus = '-';
  unsigned int R_V;
  unsigned int add,EAdd;
  unsigned char EE1,EEIN;     

  for(i=0;i<100;i++){
    gsm_data[i] = EEPROM.read(i);     
  }
  System_Enable_Disable =  EEPROM.read(254); 
  if(System_Enable_Disable == 0x30 |System_Enable_Disable == 0x31);
  else System_Enable_Disable = 0x31;
/********************************** Mobile number ******************/
  add=2;
  for(EE1=0;EE1<5;EE1++){
    for(EEIN=0;EEIN<13;EEIN++){
      PhoneNOList[EE1][EEIN]=  gsm_data[add];
      add++;
    }
  }

  /***************************************************************************/
  Read = EEPROM.read(119); if(Read == Enable | Read == 0x30)Global_Alerts_ED = Read;

  Read = EEPROM.read(120);if(Read == Enable | Read == Disable) GPRS_EN_Dis = Read;     
  /***************************************************************************/

  /***************************************************************************/
  Read = EEPROM.read(224);if(Read == Enable | Read == Disable) Sensor_1E = Read;
  Read = EEPROM.read(225);if(Read == Enable | Read == Disable) Sensor_2E = Read;
  Read = EEPROM.read(226);if(Read == Enable | Read == Disable) Sensor_3E = Read;
  Read = EEPROM.read(227);if(Read == Enable | Read == Disable) Sensor_4E = Read;
  Read = EEPROM.read(228);if(Read == Enable | Read == Disable) Sensor_5E = Read;

  Read = EEPROM.read(229);if(Read == Enable | Read == Disable) Sensor_6E = Read;
  Read = EEPROM.read(230);if(Read == Enable | Read == Disable) Sensor_7E = Read;
  Read = EEPROM.read(231);if(Read == Enable | Read == Disable) Sensor_8E = Read;
  Read = EEPROM.read(232);if(Read == Enable | Read == Disable) Sensor_9E = Read;
  Read = EEPROM.read(233);if(Read == Enable | Read == Disable) Sensor_10E = Read; 
  
  Read = EEPROM.read(234);if(Read == Enable | Read == Disable) debug_enable = Read; 

  //Read = EEPROM.read(360); Debug_Ms = Read; 

  /***************************************************************************/


  /***************************************************************************/
  Read = EEPROM.read(249);if(Read == Enable | Read == Disable) call_ED = Read;  
  Read = EEPROM.read(250);if(Read > 0  && Read < 255 ) SMS_RepetationT = Read;

  uart_send_EEPROM();

  csc_cnt=100;

  for (i=0;i<100;i++) datastr[i]=0;
  //S SMS_check();
}

  /***************************************************************************/
 /************************** uart_send_EEPROM *******************************/
/***************************************************************************/

void uart_send_EEPROM(void){
  unsigned char comma=',';
  unsigned int add;
  unsigned char EE1,EEIN,i;
  char GPRS_mes[]="GPRS,System:";
  char Humdit_mes[]="Temp:";
                      
  if(saved_EppromV==0){
    uart_send(System_Enable_Disable);uart_send(Comma1);       
    for(EE1=0;EE1<5;EE1++){       //Mobile Numbers  
      for(EEIN=0;EEIN<13;EEIN++){
        if(PhoneNOList[EE1][EEIN]>10 &&PhoneNOList[EE1][EEIN]<127){
          uart_send(PhoneNOList[EE1][EEIN]);
        }
      }
      uart_send(Comma1);
   }UART0_NL();    
             
    //Soft_printstr(Sens_EnaArr);
    len = strlen_P(Sens_EnaArr);
    for(pV=0;pV<100 & pV<len;pV++) uart_send( pgm_read_byte_near (Sens_EnaArr+pV));
    // for(pV=0;pV<100&Sens_EnaArr[pV]!=0;pV++) Soft_uart_send( Sens_EnaArr[pV]);

    uart_send(Sensor_1E);uart_send(Sensor_2E);
    uart_send(Sensor_3E);uart_send(Comma1);
    uart_send(Sensor_4E);uart_send(Sensor_4E);
    uart_send(Sensor_6E);uart_send(Comma1);
    uart_send(Sensor_7E);uart_send(Sensor_8E);uart_send(Sensor_9E);
    uart_send(Comma1); 

    print_strU0("Call SMS Rep\r");
    uart_send(call_ED); uart_send(Comma1); 
    Byte12_str =  String(SMS_RepetationT);
    Byte12_str.toCharArray(Array12B,11);print_strU0(Array12B);
       
  } 
  /***************************************************************************/    
  if(saved_EppromV==1){
    Soft_uart_send(System_Enable_Disable);  Soft_uart_send(Comma1);       
    for(EE1=0;EE1<5;EE1++){//Mobile Numbers
      for(EEIN=0;EEIN<13;EEIN++){
        if(PhoneNOList[EE1][EEIN]>10 &&PhoneNOList[EE1][EEIN]<127){
          Soft_uart_send(PhoneNOList[EE1][EEIN]);
        }
      } 
             
      Soft_uart_send(Comma1); 
    }                     
  }     
  /***************************************************************************/   
  if(saved_EppromV==2){        
       
    len = strlen_P(Sens_EnaArr);
    for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (Sens_EnaArr+pV));                      
    Soft_uart_send(Sensor_1E); Soft_uart_send(Sensor_2E);
    Soft_uart_send(Sensor_3E); Soft_uart_send(Comma1);
    Soft_uart_send(Sensor_4E); Soft_uart_send(Sensor_4E);
    Soft_uart_send(Sensor_6E); Soft_uart_send(Comma1);
    Soft_uart_send(Sensor_7E); Soft_uart_send(Sensor_8E);
    SoftUartNL();
    
          
    Soft_printstr("Call SMS Rep\r");
    Soft_uart_send(call_ED); Soft_uart_send(Comma1); 
    Byte12_str =  String(SMS_RepetationT);
    Byte12_str.toCharArray(Array12B,11);Soft_printstr(Array12B);         
  }
  saved_EppromV=12;
}

   /***************************************************************************/
  /**************************** Reboot_function ******************************/
 /***************************************************************************/
void Reboot_function(unsigned char call){
  unsigned char i;
  //char debug1str[]="GSMReboot";
  //char debug2str[]="SystemReboot";
  SMS_Del_All();
  //len = strlen_P(GSMReboot);
  //for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send(pgm_read_byte_near( GSMReboot+pV));
  //digitalWrite(GSM_Reboot_Pin,LOW); delay(2200); digitalWrite(GSM_Reboot_Pin,HIGH);delay(25000);Soft_printstr(gsm_data);
  //             len = strlen_P(SystemReboot);

  //if(call==2){for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near(SystemReboot+pV));
  resetFunc();
}

