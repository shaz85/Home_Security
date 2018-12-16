
char valid_number=0;



   //*************************************************************//
  //*********************** Message Extration  *******************//
//**************************************************************//
void Message_extraction(void){

   unsigned int i,jj,dd, char_to_int;
   char cmp_pas[8] ;
   uint8_t _idx1= text.indexOf("+CMGR:");
    _idx1=text.indexOf("\",\"",_idx1+1);
    sender_number = "";
    sender_number =  text.substring(_idx1+3,text.indexOf("\",\"",_idx1+4)); 
   
   /***************************************************************************/    
  Serial.println("number " + sender_number); 
   /************************ Valid number checking ***************************/
  if(sender_number == String(Master)) valid_number=1;
  else if (sender_number == String(Master1))valid_number=1;
  else if(1){ 
    for(i=0;i<5;i++)
      if(sender_number == String(PhoneNOList[i])){
        valid_number=i+1;break;
      }
  }
  //_idx1= text.indexOf("Mega>");
  //text = text.substring(_idx1);
  //Serial.println(text);
  text.toCharArray(Message, 150);   
  if(valid_number){print_strU0("VM $");
  strcpy(Message,strstr(Message,"Mega>"));
  
  
       
    /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
     
    
for(jj=0;Message[jj]!=0&&jj<150;jj++){
       
 //Phone number recieved for SMS alerts and calls
 if(Message[jj]=='>' && Message[jj+1]=='C' && Message[jj+2]=='1'){
    phone_numbers_Read();
    Send_SMS(1);     
    break;
  }
  /******************************************************************/
                  //Android and Non Android ALerts Enabling      
  if(Message[jj]=='C'&& Message[jj+1]=='2'){ jj+=3; 
    if(Message[jj]==Enab) System_Enable_Disable = 0x31;
    else System_Enable_Disable  = 0x30;EEPROM.write(254,System_Enable_Disable );
    
    Send_SMS(2);
    if(valid_number!=1){delay(5000);  SMS_Del_All(); Send_SMS_AlertsP2('A');}                           
    break;
  }
  /***************************************************************************/
            //Individual Sensor Alerts enable or disable
  if(Message[jj]=='C' && Message[jj+1]=='3'){jj +=3; 
    Sensor_Enable_disble(jj);
    Send_SMS(8);
    break;
  }
  /***************************************************************************/
                  //SMS alerts repetation for all kind of alerts
  if(Message[jj]=='A' && Message[jj+1]=='R'){ jj+=2;
   SMS_Repetation(jj);
   Send_SMS(3);     break;
  }

  /******************************************************************/
  
  if(Message[jj]=='S'&&Message[jj+1]=='Q'){  jj++;GSM_str_clear();str_clearF=1;   // Singal Level Checking for Module
   Soft_printstr("AT+CSQ\r");
   Check_RecievedSMS(2);   Send_SMS(5);     
   break;
   }       
  /***************************************************************************/
  if(Message[jj]=='S' && (Message[jj+1]=='E' | Message[jj+1]=='D')){ 
           if(Message[jj+1]=='D'){  Global_Alerts_ED =0x30; //Global Alerts Status Disable
                         EEPROM.write(119,0x30); Send_SMS(6);                               
           }
           else  if(Message[jj+1]=='E'){  Global_Alerts_ED = Enab; //Global Alerts Status Enable
                         EEPROM.write(119,Enab);  Send_SMS(7);  
           }
                         break;
  }

       
   /******************************************************************/
  if(Message[jj] == 'R' && Message[jj+1] == 'B'){  Send_SMS(9);delay(5000); //Recieve Reboot Command
      Reboot_function(2);                   break;
   }

  /***************************************************************************/
  if(Message[jj] == 'R' && Message[jj+1] == 'C'){jj++; Balance_AT_cmd(jj); //Recieve command to get Remaining SMS and Balance
           Soft_printstr(ATCMGF);delay(1);          Soft_printstr(ATCMGL_ALL);
           GSM_str_clear(); 
           Check_RecievedSMS(4); str_clearF=1;   
           Send_SMS(11);
           break;
   }
   /******************************************************************/
  if(Message[jj]=='G'&&Message[jj+1]=='S'){   Send_SMS(12);//Status of the system by sms
                                           
                                            break;
     }
   /***************************************************************************/
  if(Message[jj] == 'G' && Message[jj+1] == 'A'){  Send_SMS(13);//Status of the system by sms
                                            break;
     }   


  /***************************************************************************/
              //Serice activation command
  if(Message[jj] == 'Z' && Message[jj+1] == 'Z'){  jj+=2;Service_provoider(jj);Check_RecievedSMS(4);str_clearF=1;   
                         Send_SMS(11);     break;

   }
  /***************************************************************************/
              //Serice activation command
  if(Message[jj] == 'Z' && Message[jj+1] == 'T'){ // jj+=2;ZoneTimer_threshold(jj);
                         //Send_SMS(15);     break;

   }   
    /***************************************************************************/
  if(Message[jj]=='G' && (Message[jj+1]=='1' | Message[jj+1]=='2' | Message[jj+1]=='3' | Message[jj+1]=='4')){ //Send EEPROM saved values
     jj++;
          if(Message[jj]==0x31)saved_EppromV=1;
     else if(Message[jj]==0x32)saved_EppromV=2;
     else if(Message[jj]==0x33)saved_EppromV=3;
     else if(Message[jj]==0x34)saved_EppromV=4;         
     Send_SMS(16);
        break;
    }
     } //for loop
  
    /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  } //if condtion for pasword match
  
}
 


  //**************************************************************//
 //*******************  Phone Numbers Read **********************//
//**************************************************************//


void phone_numbers_Read(void){
  unsigned char EE1,EEIN,add;
  strcpy(Message,strstr(Message,"+92"));strncpy(PhoneNOList[0],Message,13);
  //2nd Number
  strcpy(Message,strstr(Message,","));strcpy(Message,strstr(Message,"+92"));strncpy(PhoneNOList[1],Message,13);
  //3rd Number
  strcpy(Message,strstr(Message,","));strcpy(Message,strstr(Message,"+92"));strncpy(PhoneNOList[2],Message,13);
  //4th Number
  strcpy(Message,strstr(Message,","));strcpy(Message,strstr(Message,"+92"));strncpy(PhoneNOList[3],Message,13);
  //5th Number
  strcpy(Message,strstr(Message,","));strcpy(Message,strstr(Message,"+92"));strncpy(PhoneNOList[4],Message,13);
  add=2;         
  for(EE1=0;EE1<5;EE1++){
    for(EEIN=0;EEIN<13;EEIN++){
        EEPROM.write(add,PhoneNOList[EE1][EEIN]);//delay(5);
        add++;
       }
    }
  for(EE1=0; EE1<5; EE1++)Serial.println(PhoneNOList[EE1]);
}


    //************************************************************//
  //******************  NSensor_Enable_disble  ******************//
//**************************************************************//

void Sensor_Enable_disble(unsigned char addres){
     
     Sensor_1E = Message[addres++];  EEPROM.write(224,Sensor_1E); addres++;
     Sensor_2E = Message[addres++];  EEPROM.write(225,Sensor_2E); addres++;
     Sensor_3E = Message[addres++];  EEPROM.write(226,Sensor_3E); addres++;
     
     
     Sensor_4E = Message[addres++];  EEPROM.write(227,Sensor_4E); addres++;
     Sensor_5E = Message[addres++];  EEPROM.write(228,Sensor_5E); addres++;
     Sensor_6E = Message[addres++];  EEPROM.write(229,Sensor_6E); addres++;
   
     Sensor_7E = Message[addres++];  EEPROM.write(230,Sensor_7E); addres++;
     Sensor_8E = Message[addres++];  EEPROM.write(231,Sensor_8E); addres++;
     //Sensor_9E  = Message[addres++]; EEPROM.write(232,Sensor_9E);
     
     addres++;
     //Sensor_10E = Message[addres++]; EEPROM.write(233,Sensor_10E);
     
     //Debug_Ms = Message[addres++]; EEPROM.write(233,Debug_Ms);
     

}



    //************************************************************//
  //*******************  ZoneTimer_threshold  *********************//
//**************************************************************//
void ZoneTimer_threshold(unsigned char addres){
     char data12[6],i; 
     int temp;
       for(i=0;i<5;i++){
        if(Message[addres]==','){addres++;break;}
           data12[i]=Message[addres++];
       }data12[i]=0;
       
    ZoneFire_CntSet= atoi(data12);

    for(i=0;i<5;i++){
        if(Message[addres]==','){addres++;break;}
           data12[i]=Message[addres++];
       }data12[i]=0;
       
    zone_FireTH= atoi(data12);
   
   if(ZoneFire_CntSet > 50 && ZoneFire_CntSet < 10000){
    temp = ZoneFire_CntSet;
    i = temp;
    temp >>=8;
    EEPROM.write(241,i);EEPROM.write(242,temp);
   }
   if(zone_FireTH>100 && zone_FireTH < 1024){
      temp = zone_FireTH;
      i = temp;
      temp >>=8;
      EEPROM.write(243,i);EEPROM.write(244,temp);
   
   }
   
}

     //************************************************************//
  //*******************  ZoneTimer_threshold  *********************//
//**************************************************************//

void SMS_Repetation(unsigned char addres){
      char data12[6],i; 
      if(Message[addres]==Enable){
        call_ED=Enable;
        
      }
      else call_ED=Disable;
       EEPROM.write(249,call_ED);
      addres++;
       if(Message[addres]==','){addres++;
      for(i=0;i<3;i++){
        if(Message[addres]==','){addres++;break;}
           data12[i]=Message[addres++];
       }data12[i]=0;UART0_NL();
       //Soft_printstr("Hello");
       //Soft_printstr(data12);Soft_printstr("Hello");
       UART0_NL();
    SMS_RepetationT = atoi(data12);
    if(SMS_RepetationT > 0 && SMS_RepetationT < 250)
       EEPROM.write(250 , SMS_RepetationT);
    else SMS_RepetationT = 1;
  }
}


