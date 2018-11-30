

  //**************************************************************//
 //********************* Timer 1 Interrupt **********************//
//**************************************************************//

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  //generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  Touch_1Sec=0;
  one_sec++;Packet_Send_Time++;
  Repeat_SMS_Reply++;
  if(Repeat_SMS_Reply>0)Repeat_SMS_Reply=70;
 
  if(one_sec >59){ one_sec =0; All_Time++; thisRUN_Time++;}
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
