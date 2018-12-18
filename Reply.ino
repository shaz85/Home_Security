
  //**************************************************************//
 //**************************** GSM_AT  *************************//
//**************************************************************//

void new_Line(void){print_strU0("\r");}

void Send_SMS(unsigned char val){
  unsigned char temp[4],temp1[7],const_arr;
  unsigned int i,j,tempDays,tempMinute, tempHours;
  if(str_clearF!=1)
    GSM_str_clear();
  //UART0_NL();
  SoftUartNL();
  //Soft_printstr("R");
  delay(10);Soft_printstr(ATCMGF);delay(10);
  //for(i=0;i<100&ATCSCS[i]!=0;i++)
  //  uart_send( ATCSCS[i]); 
  delay(10);
  Soft_printstr(ATCMGS);Soft_uart_send('"');
  Soft_printstr(M_Recv_numb);
  Soft_uart_send('"');SoftUartNL();delay(1800);

 /***************************************************************************/
  if(val == 1){  //Send Save Number in EEPROM cmd 1
    for(i=0;i<5;i++){
      for(j=0;j<13;j++){
        if((PhoneNOList[i][j]>=0x30&&PhoneNOList[i][j]<=0x39)|PhoneNOList[i][j]=='+')
          Soft_uart_send(PhoneNOList[i][j]);           
      } Soft_uart_send(',');
    }saved_EppromV=12;  
  }
 
 /***************************************************************************/
  //Alert Message for any sensor out of range
  else if (val == 2){   //print_strU0("The System is ");
    if(System_Enable_Disable == 0x31){len = strlen_P(SystemEn);
      for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (SystemEn+pV));
       // Door_Sensor_Status(2); 
        DoorOpened(); saved_EppromV = 100;
    }
    else{len = strlen_P(SystemEnDis);
      for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (SystemEnDis+pV));}

    Zone1_Status = 0; Zone2_Status = 0; Zone3_Status = 0; Zone4_Status = 0;
    Zone5_Status = 0; Zone6_Status = 0; Zone7_Status = 0; Zone8_Status = 0;            
             
  }
 /***************************************************************************/
  //Alert Message for any sensor out of range
  else if (val == 3){   
    len = strlen_P(Call_ED);     
    for(pV=0;pV<100 &pV<len;pV++) Soft_uart_send( pgm_read_byte_near (Call_ED+pV));
    //for(i=0;i<100&Call_ED[i]!=0;i++) uart_send( Call_ED[i]); //print_strU0("Call E/D Repetation ");Call_ED
    Soft_uart_send(call_ED);
    Soft_uart_send(',');

    Byte12_str =  String(SMS_RepetationT);
    Byte12_str.toCharArray(Array12B,11);Soft_printstr(Array12B);  
  }            
 /***************************************************************************/
  //Alert Message for any sensor out of range
       /*else if (val == 4){ 
              if(Turn_OFF_Buzzer==0x31)  
              print_strU0("Buzzer will ON if alert");
              else  print_strU0("Buzzer is OFF");
            }  */          
 /***************************************************************************/
     
  else if (val == 5){ for(i=0;i<200;i++)Message[i]=0;
    strncpy(Message,gsm_data,12);
    Soft_printstr(Message);
  }
 /***************************************************************************/
       
  else if (val== 6 |val== 7 ){ //delay(2000);
    len = strlen_P(SysAlerts);     
    for(pV=0;pV<100 &pV<len;pV++) Soft_uart_send( pgm_read_byte_near (SysAlerts+pV));
    // for(i=0;i<100&SysAlerts[i]!=0;i++) uart_send( SysAlerts[i]);
    //print_strU0("SysAlerts = ");
    if(Global_Alerts_ED==Enab)
      Soft_uart_send('E');
    else Soft_uart_send('D');
  }
 /***************************************************************************/
       //Thresh hold  for humidity and Temperature cmd 2
  else if (val== 8 ){ //delay(2000);
    len = strlen_P(Sens_EnaArr);
    for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (Sens_EnaArr+pV));
                      
    Send_SMS_Phase2(1);
  }
          
 /***************************************************************************/
       //Thresh hold  for humidity and Temperature cmd 2
  else if (val == 9){ //delay(2000);
    len = strlen_P(Reboot);
    for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (Reboot+pV));
    //print_strU0("Reboot");
  }
        
  /***************************************************************************/
            //Alert Message for any sensor out of range
  else if (val == 11){ //if(Message[++jj]=='1')
    // Soft_printstr("Reply\r");
    Soft_printstr(gsm_data);
  }
 /***************************************************************************/
       //Thresh hold  for humidity and Temperature cmd 2
  else if (val == 12){ //delay(2000);j=0;
    Status_Message();
    //Soft_printstr("Shaz is great");
    saved_EppromV = 100;
           
  }
  /***************************************************************************/
       //Thresh hold  for humidity and Temperature cmd 2
  else if (val == 13){ 
    String_send();  
  }         

  /***************************************************************************/
            //Alert Message for any sensor out of range
     /*  else if (val == 14){ //if(Message[++jj]=='1')
              //print_strU0("Reply\r");
              print_strU0(gsm_data);
            }*/
  /***************************************************************************/
      //Alert Message for any sensor out of range
  else if (val == 15){
       
  }      
 /***************************************************************************/
  //Off set and Wapda and DG and Power_Failure_Time setting
  else if (val==16){
    uart_send_EEPROM();
  }

 /***************************************************************************/
 /***************************************************************************/
  delay(10);//GSM_str_clear();
  Soft_uart_send(CTRL_Z);SoftUartNL();          
           print_strU0("SSS\r");
  for(i=0;i<5;i++){  
    Check_RecievedSMS(10); 
    if((strstr(gsm_data, "+CMGS:"))!=0)break;
  }  
  if(saved_EppromV == 100){saved_EppromV= 99;  delay(8000);}    
  print_strU0(gsm_data);print_strU0("SSS\r");
   //SoftUartNL();Soft_printstr("R-");
           
 }
 
  /***************************************************************************/
 /***************************************************************************/
/***************************************************************************/
 
void Send_SMS_Phase2(unsigned char val){
    

  Soft_uart_send(Sensor_1E);Soft_uart_send(Sensor_2E);
  Soft_uart_send(Sensor_3E);Soft_uart_send(Comma1);

  Soft_uart_send(Sensor_4E);Soft_uart_send(Sensor_5E);
  Soft_uart_send(Sensor_6E);Soft_uart_send(Comma1);

  Soft_uart_send(Sensor_7E);Soft_uart_send(Sensor_8E);
  //uart_send(Sensor_9E);uart_send(Comma1);

  //uart_send(Sensor_10E);
}

  /***************************************************************************/
 /***************************************************************************/
/***************************************************************************/
void Timeprint(unsigned int value){
  Byte12_str =  String(value);
  Byte12_str.toCharArray(Array12B,11);
  print_strU0(Array12B);
  print_strU0(",");
}
   /***************************************************************************/
  /***************************************************************************/
 /***************************************************************************/
void Status_Message(void ){
   if(Sensor_1E == 0x31){
      Soft_printstr(Store_str);          Soft_uart_send(one); Soft_printstr(Door_str);
      if(!digitalRead(ZONE1_PIN))        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();}
 /***************************************************************************/
   if(Sensor_2E == 0x31){   
      Soft_printstr(Store_str);          Soft_uart_send(two); Soft_printstr(Door_str);
      if(!digitalRead(ZONE2_PIN))        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();
   }        
 /***************************************************************************/
   if(Sensor_3E == 0x31){
      Soft_printstr(Store_str);          Soft_uart_send(three); Soft_printstr(Door_str);
      if(!digitalRead(ZONE3_PIN))        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();
   }        
 /***************************************************************************/
   if(Sensor_4E == 0x31){   
      Soft_printstr(Store_str);          Soft_uart_send(four); Soft_printstr(Door_str);
      if(!digitalRead(ZONE4_PIN))        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();
   }       
 /***************************************************************************/
   if(Sensor_5E == 0x31){   
      Soft_printstr(Store_str);             Soft_uart_send(five); Soft_printstr(Door_str);
      if(Zone5_Prev ==  Door_closed)        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();
   }       
 /***************************************************************************/
    if(Sensor_6E == 0x31){  
      Soft_printstr(Store_str);             Soft_uart_send(six); Soft_printstr(Door_str);
      if(Zone6_Prev ==  Door_closed)        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();
    }       
 /***************************************************************************/
   if(Sensor_7E == 0x31){  
      Soft_printstr(Store_str);             Soft_uart_send(seven); Soft_printstr(Door_str);
      if(Zone7_Prev ==  Door_closed)        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();
   }       
 /***************************************************************************/
  if(Sensor_8E == 0x31){    
      Soft_printstr(Store_str);             Soft_uart_send(eight); Soft_printstr(Door_str);
      if(Zone8_Prev ==  Door_closed)        Soft_printstr(Colse_str);
      else Soft_printstr(Open_str);
            SoftUartNL();
  }       
 /***************************************************************************/
//print_strU0("SSS\r");  
 // Soft_uart_send(CTRL_Z); delay(5000); 

  
}


  //**************************************************************//
 //**************************** GSM_AT  *************************//
//**************************************************************// 

void DoorOpened(void){
   
  if(Zone1_Status == 1 | Zone2_Status == 1 | Zone3_Status == 1 | Zone4_Status == 1 | Zone5_Status == 1 | Zone6_Status == 1 | Zone7_Status == 1 | Zone8_Status == 1  ){
        UART0_NL(); 
        len = strlen_P(DoorOpen);
        for(pV=0;pV<100 & pV<len;pV++) Soft_uart_send( pgm_read_byte_near (DoorOpen+pV));
     
       
       
       SoftUartNL();
      if(Zone1_Status == 1 && Sensor_1E == 0x31){
             Soft_uart_send(one);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();
          Zone1_Status=0;
      }
      if(Zone2_Status == 1 && Sensor_2E == 0x31){
              Soft_uart_send(two);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();    Zone2_Status=0;
      }
      if(Zone3_Status == 1 && Sensor_3E == 0x31){
             Soft_uart_send(three);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();     Zone3_Status=0;
      }
      if(Zone4_Status == 1 && Sensor_4E == 0x31){
              Soft_uart_send(four);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();    Zone4_Status=0;
      }
      if(Zone5_Status == 1 && Sensor_5E == 0x31){
             Soft_uart_send(five);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();    Zone5_Status=0;
      }
      if(Zone6_Status == 1 && Sensor_6E == 0x31){
             Soft_uart_send(six);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();    Zone6_Status=0;
      }
      if(Zone7_Status == 1 && Sensor_7E == 0x31){
              Soft_uart_send(seven);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();    Zone7_Status=0;
      }
      if(Zone8_Status == 1 && Sensor_8E == 0x31){
              Soft_uart_send(eight);    Soft_printstr(Door_str);
          Soft_printstr(Open_str);     SoftUartNL();    Zone8_Status=0;
      }
   }  
     
}



    //************************************************************//
  //**********  SMS AT command from Remote position  ************//
//**************************************************************//


void Service_provoider(unsigned char recv){
  SMS_Del_All();
  //delay(1000);//asm clrwdt

  Soft_printstr(ATCMGF); delay(100);
  Soft_printstr(ATCMGS);Soft_uart_send('"');
  GSM_str_clear();  
  for(;recv<250;recv++){
    if(Message[recv]=='!')break;
    else{ uart_send(Message[recv]); Soft_uart_send(Message[recv]);}
  }               
   Soft_uart_send('"');SoftUartNL();delay(1000);recv++;
  for(;recv<250;recv++){
    if(Message[recv]=='!')break;
    else{ uart_send(Message[recv]); Soft_uart_send(Message[recv]);}
   }                //Soft_uart_send('$');
   
  Soft_uart_send(CTRL_Z);
  delay(12000);//asm clrwdt
  Soft_printstr(ATCMGF);delay(1);
  Soft_printstr(ATCMGL_ALL);delay(1); GSM_str_clear();

}


    //************************************************************//
  //****************  Find Blance using AT cmd  *****************//
//**************************************************************//

void Balance_AT_cmd(unsigned char recv){
  unsigned char val,i=0;

  GSM_str_clear();val = recv+1;
  SMS_Del_All();//UART0_NL();
  
  Soft_printstr(ATCMGF);delay(30);//Soft_uart_send('$');
   //UART1_Write_Text("AT+CUSD=1,\"*124#\",15\r");
  for(;val<250&&Message[val]!=0;val++){
    if(Message[val]=='!')break;
    if(Message[val]>6 && Message[val]<127){
      Soft_uart_send(Message[val]);
      //uart_send(Message[val]);
    }
  }

  Soft_printstr("\r"); 
   
   delay(8000);
  // asm clrwdt
}

    //************************************************************//
  //****************  Humidity and Temperatue  ******************//
//**************************************************************//
void humidity_tempr_threshhold(unsigned char val){
  
     

}
   
   
void String_send(void){
  if(Sensor_1E == 0x31){
    Soft_uart_send(one);      Soft_printstr(Door_str);
    if(Zone1_Prev ==  Door_closed)        
      Soft_printstr(Colse_str);
    else 
      Soft_printstr(Open_str);
    SoftUartNL();
  }
  /***************************************************************************/
  if(Sensor_2E == 0x31){   
    Soft_uart_send(two); Soft_printstr(Door_str);
    if(Zone2_Prev ==  Door_closed)        Soft_printstr(Colse_str);
    else Soft_printstr(Open_str);
    SoftUartNL();
  }        
  /***************************************************************************/
  if(Sensor_3E == 0x31){
    Soft_uart_send(three); Soft_printstr(Door_str);
    if(Zone3_Prev ==  Door_closed)        Soft_printstr(Colse_str);
    else Soft_printstr(Open_str);
    SoftUartNL();
  }        
  /***************************************************************************/
  if(Sensor_4E == 0x31){   
    Soft_uart_send(four); Soft_printstr(Door_str);
    if(Zone4_Prev ==  Door_closed)        Soft_printstr(Colse_str);
    else Soft_printstr(Open_str);
    SoftUartNL();
  }       
  /***************************************************************************/
  if(Sensor_5E == 0x31){   
    Soft_uart_send(five); Soft_printstr(Door_str);
    if(Zone5_Prev ==  Door_closed)        Soft_printstr(Colse_str);
    else Soft_printstr(Open_str);
    SoftUartNL();
  }       
  /***************************************************************************/
  if(Sensor_6E == 0x31){  
    Soft_uart_send(six); Soft_printstr(Door_str);
    if(Zone6_Prev ==  Door_closed)        Soft_printstr(Colse_str);
    else Soft_printstr(Open_str);
    SoftUartNL();
  }       
  /***************************************************************************/
  if(Sensor_7E == 0x31){  
    Soft_uart_send(seven); Soft_printstr(Door_str);
    if(Zone7_Prev ==  Door_closed)        Soft_printstr(Colse_str);
    else Soft_printstr(Open_str);
    SoftUartNL();
  }       
  /***************************************************************************/
  if(Sensor_8E == 0x31){    
    Soft_uart_send(eight); Soft_printstr(Door_str);
    if(Zone8_Prev ==  Door_closed)        Soft_printstr(Colse_str);
    else Soft_printstr(Open_str);
      SoftUartNL();
  }       
 /***************************************************************************/

}   


