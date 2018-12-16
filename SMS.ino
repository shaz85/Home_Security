

/***************************************************************************/
 /******************************* SMS_Del_All *******************************/
/***************************************************************************/

void SMS_Del_All(void){
  unsigned int i,j;
  delay(1000);               
  Soft_printstr(ATCMGF);delay(5);
  GSM_str_clear();
  len = strlen_P(ATQMGDA);
  for(i=0; i<100 & i<len; i++) 
  Soft_uart_send( pgm_read_byte_near (ATQMGDA+i));          

   for(i=0;i<8430;i++){
    if(mySerial.available())
      gsm_data[recv_cnt++] = mySerial.read(); 
    delay(1);  
    if(recv_cnt>148)
      recv_cnt=147;
  }
  print_strU0("Dell " );
    print_strU0(gsm_data);GSM_str_clear();
  //Soft_uart_send
  print_strU0("S " );
      
}

  /***************************************************************************/
  /********************************* SMS_check *******************************/
 /***************************************************************************/

void SMS_check(void){      
    
  //Soft_printstr(ATCMGL_ALL); 
  text = Sim800l.readSms(1);
  //Serial.println(text);
   
  if(text.length() > 35){ // New SMS Arrive 
    Serial.println(F("New message"));   
    Message_extraction();           
    Sim800l.delAllSms();  
    Sim800l.delAllSms();      
  }
}

  /*************************************************************************/
 /**************************** Check_RecievedSMS **************************/
/*************************************************************************/

void Check_RecievedSMS(unsigned char delay_seconds){
     long int i;    
     //recv_cnt=0;
  if(delay_seconds == 100){delay_seconds=3;  
     SoftUartNL();
  }

  for(i=0; i < (1000 * delay_seconds ); i++){
    if(mySerial.available()){
      gsm_data[recv_cnt++] = mySerial.read(); i=0; 
      uart_send(mySerial.read());
    }
    delayMicroseconds(50);
    if(recv_cnt>248)recv_cnt=247;
  }
  
     

}

