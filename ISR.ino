

  //**************************************************************//
 //********************* Timer 1 Interrupt **********************//
//**************************************************************//
unsigned int cont_v=0;
ISR(TIMER2_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  //generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
 
   //digitalWrite(13, digitalRead(13) ^ 1);
  if(cont_v > 10){
    if(zone1_in_alert){
      if(digitalRead(ZONE1_PIN))
          zone1_up_debounce++;
      else if(!digitalRead(ZONE1_PIN))
        zone1_down_debounce++; 
    }
    if(zone2_in_alert){

      if(digitalRead(ZONE2_PIN))
        zone2_up_debounce++; 
      else if(!digitalRead(ZONE2_PIN))
        zone2_down_debounce++;
    }

    if(zone3_in_alert){
      if(digitalRead(ZONE3_PIN))
        zone3_up_debounce++; 
      else if(!digitalRead(ZONE3_PIN))
        zone3_down_debounce++;
    }
    
    if(zone4_in_alert){
      if(digitalRead(ZONE4_PIN))
        zone4_up_debounce++; 
      else if(!digitalRead(ZONE4_PIN))
        zone4_down_debounce++;
    }
    cont_v=0;
  }cont_v++;
}

  //**************************************************************//
 //**************************** GSM_AT  *************************//
//**************************************************************//
ISR(USART_RX_vect)  {
       datastr[dat_cnt] = UDR0;
       if(datastr[dat_cnt]>0x1 && datastr[dat_cnt]<250)
         dat_cnt++;

       if(dat_cnt>=98)dat_cnt=96; 
}


void uart_send(unsigned char dat) {
 while(! (UCSR0A & ( 1 << UDRE0))  );  // until dararegister is NOT empty 
 UDR0 = dat;                           
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
       uart_send(str[i]);
}
  /***************************************************************************/
 /***************************************************************************/

void print_StrU0(String str)
{int i;
      for(i=0;str[i]&& i<240;i++)
      if(str[i]> 0x01 && str[i] < 250)
       uart_send(str[i]);
}  
void UART0_NL(void){
uart_send(10);uart_send(13);
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
