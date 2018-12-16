

  //**************************************************************//
 //********************* Timer 1 Interrupt **********************//
//**************************************************************//
char flagV=0,toggle0=1 ;

ISR(TIMER2_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
    cnt++;


  if(bitRead(alert_status_flag, FIRST_BIT)){
    if(digitalRead(ZONE1_PIN))
      zone1_up_debounce++;
    else if(!digitalRead(ZONE1_PIN))
      zone1_down_debounce++; 
  }
  if(bitRead(alert_status_flag, SECOND_BIT)){

    if(digitalRead(ZONE2_PIN))
      zone2_up_debounce++; 
    else if(!digitalRead(ZONE2_PIN))
      zone2_down_debounce++;
  }

  if(bitRead(alert_status_flag, THIRD_BIT)){
    if(digitalRead(ZONE3_PIN))
      zone3_up_debounce++; 
    else if(!digitalRead(ZONE3_PIN))
      zone3_down_debounce++;
  }
  
  if(bitRead(alert_status_flag, FOURTH_BIT)){

    if(digitalRead(ZONE4_PIN))
      zone4_up_debounce++; 
    else if(!digitalRead(ZONE4_PIN))
      zone4_down_debounce++;
  }

}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  //generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  //TCNT1 = 63535;
  Touch_1Sec=0;
  /*
  if(flagV == 0){
    digitalWrite(8, HIGH);
    flagV++;
  }
  else if(flagV == 1){
    digitalWrite(8, LOW);
    flagV=0;
  }
  */
  
  

  
  /*one_sec++;Packet_Send_Time++;
  Repeat_SMS_Reply++;
  if(Repeat_SMS_Reply>0)Repeat_SMS_Reply=70;
 
  if(one_sec >59){ one_sec =0; All_Time++; thisRUN_Time++;}
  */
}

  //**************************************************************//
 //**************************** GSM_AT  *************************//
//**************************************************************//
/*       datastr[dat_cnt] = UDR0;
       if(datastr[dat_cnt]>0x1 && datastr[dat_cnt]<250)
         dat_cnt++;

       if(dat_cnt>=98)dat_cnt=96; 
}

*/
void uart_send(char dat) {
  Serial.write(dat);
                            
}

unsigned char uart_read() {
 while(!  (UCSR0A & (1 << RXC0)) );  // until Receive complete is NOT complete 
 return UDR0;
}
 /****************************UART 0 ***********************************/
 /***************************************************************************/
void print_strU0(char *str)
{int i;
      for(i=0;str[i]&& i<240;i++)
      if(str[i]> 0x01 && str[i] < 250)
       Serial.write(str[i]);
}
  /***************************************************************************/
 /***************************************************************************/

void print_StrU0(String str)
{int i;
      for(i=0;str[i]&& i<240;i++)
      if(str[i]> 0x01 && str[i] < 250)
       Serial.write(str[i]);
}  
void UART0_NL(void){
Serial.println("");
}
  /***************************************************************************/
 /***************************************************************************/
/***************************************************************************/

void Soft_printstr(char *str)
{int i;
      
       for(i=0;str[i] && i<240;i++)
         if(str[i]> 0x01 && str[i] < 250)
         mySerial.write(str[i]);
     
}
/***************************************************************************/
void Soft_uart_send(unsigned char dat){     
       mySerial.write(dat);
     
}
/***************************************************************************/
void SoftUartNL(){
      mySerial.write(10);mySerial.write(13);
}
/***************************************************************************/

/***************************************************************************/
 /***************************************************************************/

 void GSM_str_clear(void){
   unsigned int i;
   
   for(i=0;i<250;i++)
     gsm_data[i]=0;
     recv_cnt=0;
 }
