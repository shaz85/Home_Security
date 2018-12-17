

  /***************************************************************************/
 /******************************* SMS_Del_All *******************************/
/***************************************************************************/

void SMS_Del_All(void){
  unsigned int i,j;
  delay(1000);               
  Soft_printstr(ATCMGF);delay(5);
  GSM_str_clear();
  len = strlen_P(ATQMGDA);
  for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (ATQMGDA+pV));          

  for(i=0;i<8430;i++){
    if(mySerial.available())
      gsm_data[recv_cnt++] = mySerial.read(); 
    delay(1);  
    if(recv_cnt>148)recv_cnt=147;
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

  unsigned int i,jj,add;
  unsigned char New_SMS=0;

  GSM_str_clear();   Soft_printstr(ATCMGF);delay(5);

  if(csc_cnt >10){
    len = strlen_P(ATCPMS);GSM_str_clear();
    for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (ATCPMS+pV));           
    for(i=0;i<5300;i++){if(mySerial.available())gsm_data[recv_cnt++] = mySerial.read(); delay(1);  if(recv_cnt>248)recv_cnt=247;}       
    print_strU0(gsm_data);GSM_str_clear();
    csc_cnt = 0 ; 
  }
  Soft_printstr(ATCMGL_ALL); 
  Check_RecievedSMS(3); 
   
  if(recv_cnt > 35){ // New SMS Arrived
      
    for(jj=0;jj<150;jj++) Message[jj]=0;//Array initlization
    print_strU0("New");  
    print_strU0(gsm_data);
    if( strstr(gsm_data,"+CMGL:")!=0){
      //print_strU0(gsm_data);
      Message_extraction();           
      SMS_Del_All();
    }
  }
}
  /***************************************************************************/
 /********************************* New_SMS_check *******************************/
/***************************************************************************/
void Check_RecievedSMS(unsigned char Val){
  long int i;    
  //recv_cnt=0;
  if(Val == 100){
    Val=4;  
    print_strU0("New\r");
    SoftUartNL();
  }

  for(i=0;i<(55000*Val);i++){
    if(mySerial.available()){
      gsm_data[recv_cnt] = mySerial.read(); i=0;
      if(Val == 4 && gsm_data[recv_cnt] == '>'){        
        print_strU0("found>\r");
        break;      
      }
      if(strstr(gsm_data, "+CMGS") && Val ==10)
        i = (55000*Val) - 20;

      recv_cnt++;
    }
    
       
    if(recv_cnt>248)recv_cnt=247;
  }
}

