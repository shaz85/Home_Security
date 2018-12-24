 
  //**************************************************************//
 //**************************** GSM_AT  *************************//
//**************************************************************//
void Security_call(void){
  unsigned char i,j,k,dd;//Soft_printstr("First\r");
  k=0;
  for(i=0;i<5;i++){         
    if(PhoneNOList[i][0]=='+'|PhoneNOList[i][1]=='9'){ 
      GSM_str_clear();
      Soft_printstr("ATD");
      for(j=0;j<13;j++){
        if((PhoneNOList[i][j]>=0x30&&PhoneNOList[i][j]<=0x39)|PhoneNOList[i][j]=='+')
          Soft_uart_send(PhoneNOList[i][j]);//Delay_us(1);
      }
      Soft_printstr(";\r");res =strstr(gsm_data,"BUSY"); 
      for(j=1;j<10;j++){
        Check_RecievedSMS(2);                  
        if(j%3==0) res =strstr(gsm_data,"BUSY"); 
        else if(j%5==0) res =strstr(gsm_data,"NO ANSWER");
        //else if(j%10==0) print_strU0(gsm_data);
        else if(j%8==0) res =strstr(gsm_data,"ERROR");
        if(res!=0){
          Soft_printstr(gsm_data);         
          break;
        }
        delay(1000);                 
                   
      }
      uart_send(i|0x30);              
      print_strU0("VM\r");
      Soft_printstr("ATH\r");
      print_strU0(gsm_data);delay(2000);
      GSM_str_clear();
    }
  }  
}
  //**************************************************************//
 //**************************** GSM_AT  *************************//
//**************************************************************// 
char SMS_cnt=0;
void Send_SMS_AlertsP2(unsigned char cmd){
  int i,j,i1;
  char cnt_1;
  unsigned char send_1,ithState;SMS_cnt=0;
  for(i=0;i<5;i++){
    SoftUartNL();
    if(PhoneNOList[i][0]=='+'|PhoneNOList[i][1]=='9'){
      //UART0_NL();
      Soft_printstr(ATCMGF);
      delay(2);
      Soft_printstr(ATCMGS);
      Soft_uart_send('"');
      for(j=0;j<13;j++){
         if((PhoneNOList[i][j]>=0x30&&PhoneNOList[i][j]<=0x39)|PhoneNOList[i][j]=='+')
            Soft_uart_send(PhoneNOList[i][j]);//Delay_us(1);
      }
      GSM_str_clear(); send_1=0; 
      Soft_uart_send('"');
      Check_RecievedSMS(100);
      uart_send(i|0x30);      
      res = strchr(gsm_data, '>');

      if(res!=0) uart_send('>');
           
      
      switch (cmd) {
     
 /******************************************************************/       
        case 'A':
             
             
          if(System_Enable_Disable == 0x31){len = strlen_P(SystemEn);
              for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (SystemEn+pV));
          }
          else{len = strlen_P(SystemEnDis);
              for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (SystemEnDis+pV));}

          len = strlen_P(thisNumber);
          for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (thisNumber+pV));
          Soft_printstr(M_Recv_numb);
          break;
        /******************************************************************/  
        case 1:            //Zone 1
          //Soft_printstr(Store_str);      
          Soft_printstr(Door_str); Soft_uart_send(one);
          Soft_printstr(Open_str);           
          break;
          
           //Zone 2
        /******************************************************************/  
        case 2:
          Soft_printstr(Door_str);  Soft_uart_send(two);
          Soft_printstr(Open_str);
          break;           
      
        /******************************************************************/       
        case 3:            // Zone 3
          Soft_printstr(Door_str);  Soft_uart_send(three);
          Soft_printstr(Open_str);
          break;     
        /******************************************************************/       
        case 4:            // Zone 4
          Soft_printstr(Door_str);  Soft_uart_send(four);
          Soft_printstr(Open_str);
          break;
        /******************************************************************/  
        case 5:            // Zone 5           
          Soft_printstr(Door_str);  Soft_uart_send(five);
          Soft_printstr(Open_str);
          break; 

        /******************************************************************/       
        case 6:            // Zone 6
          Soft_printstr(Door_str);  Soft_uart_send(six);
          Soft_printstr(Open_str);
          break;
        /******************************************************************/  
        case 7:            // Zone 7
          Soft_printstr(Door_str);  Soft_uart_send(seven);
          Soft_printstr(Open_str);
          break;

        /******************************************************************/       
        case 8:            // Zone 8
          Soft_printstr(Door_str);  Soft_uart_send(eight);
          Soft_printstr(Open_str);
          break;
        /******************************************************************/  
        case 32:           
          break;          
      }
      
      /******************************************************************/      
      Soft_uart_send(CTRL_Z); SoftUartNL(); Check_RecievedSMS(10);
      if(1){
        send_1=0;
        res = strstr(gsm_data, "MGS");delay(2000); //Soft_uart_send('+');
        if(res!=0){ send_1=1; uart_send('Y');}
      }
      if(cmd == 'A')break;
      delay(500); //asm clrwdt
      GSM_str_clear();    
      SMS_cnt++;
      if(SMS_cnt>8)break;
    } // if phone number exist

  }// for loop 
}




