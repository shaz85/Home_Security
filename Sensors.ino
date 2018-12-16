char Alarm=0;

void Battery_Voltage(void){
 
}

unsigned char message_send_zones=0;
unsigned char stability_sensor_cnt = 60;
  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
void sensors_status_check(void){
    // Fire_sensor();
  static unsigned char sendDebug=0;
  if(System_Enable_Disable == 0x31 ){      
    
    if(Sensor_1E == 0x31 && zone1_up_debounce > stability_sensor_cnt){
      zone1_up_debounce = stability_sensor_cnt;
      zone1_down_debounce = 0;
      if(sendDebug==0){
        print_strU0("open \r\n");
        sendDebug=1;
      }

      if(bitRead(message_send_flag1, FIRST_BIT) ){  
        bitClear(alert_status_flag, FIRST_BIT);   
        Send_SMS_AlertsP2(1);Zone1_Status=0; if(call_ED== Enable) Security_call();
        bitClear(message_send_flag1, FIRST_BIT);
        bitSet(alert_status_flag, FIRST_BIT); 
        print_strU0("Alerts\r");
      }
    }

    else if(zone1_down_debounce > stability_sensor_cnt){        
      zone1_up_debounce = stability_sensor_cnt ;
      zone1_down_debounce = 0;
      zone1_up_debounce = 0;
      if(sendDebug==1){
       print_strU0("NoAlerts  \r\n");
        sendDebug=0;
      } 
      bitSet(message_send_flag1, FIRST_BIT);
    }
    
/*

    if(Zone1_Status == 1 && Sensor_1E == 0x31 && zone1_up_debounce > stability_sensor_cnt){
      if(message_send_zones && 0xFE){     
        Send_SMS_AlertsP2(1);Zone1_Status=0; if(call_ED== Enable) Security_call();
      }
      else{
        message_send_zones |=0x01;
        zone2_up_debounce = stability_sensor_cnt + 2;
        zone2_down_debounce = 0;
      }
    }
     
    
    if(Zone3_Status == 1 && Sensor_3E == 0x31 && zone3_up_debounce > stability_sensor_cnt){
      if(message_send_zones && 0xFE){     
        Send_SMS_AlertsP2(3);Zone4_Status=0; if(call_ED== Enable) Security_call();
      }
      else{
        message_send_zones |=0x04;
        zone3_up_debounce = stability_sensor_cnt + 2;
        zone3_down_debounce = 0;
      }
    }


    if(Zone4_Status == 1 && Sensor_4E == 0x31 && zone4_up_debounce > stability_sensor_cnt){
      if(message_send_zones && 0xF7){     
        Send_SMS_AlertsP2(4);Zone4_Status=1; if(call_ED== Enable) Security_call();
      }
      else{
        message_send_zones |=0x08;
        zone4_up_debounce = stability_sensor_cnt + 2;
        zone4_down_debounce = 0;
      }
    }
    

    else if(Zone5_Status == 1 && Sensor_5E == 0x31){
      Send_SMS_AlertsP2(5);Zone5_Status=0; if(call_ED== Enable) Security_call();}
    
    else if(Zone6_Status == 1 && Sensor_6E == 0x31){
      Send_SMS_AlertsP2(6);Zone6_Status=0; if(call_ED== Enable) Security_call();}
    
    else if(Zone7_Status == 1 && Sensor_7E == 0x31){
      Send_SMS_AlertsP2(7);Zone7_Status=0; if(call_ED== Enable) Security_call();}
    
    else if(Zone8_Status == 1 && Sensor_8E == 0x31){
      Send_SMS_AlertsP2(8);Zone8_Status=0; if(call_ED== Enable) Security_call();}  
    */   
  }
  else {
          digitalWrite(Buzzer_ON_1, LOW); Alarm = 0;digitalWrite(Red_led, LOW);
      
     }

}



  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
char alarm_Zone=0;
void Fire_sensor(void){
       //************************* Zone 1 on fire check ***********************//
            
}



  //**************************************************************//
 //********************** Home_S_sensorsSt  *********************//
//**************************************************************//
void Home_S_sensorsSt( char Door_No,  char Door_V){
    
     switch(Door_No){
     
       case 0x31:                      
            if(Door_V == Door_closed ) {   Zone1_Prev = Door_closed; Zone1_Status = 0; }
            else if(Door_V == Door_Open ){ Zone1_Prev = Door_Open;   Zone1_Status = 1; }
            data_EEPROM[0] = Zone1_Prev;            
            EEPROM.write(300, Zone1_Prev );
             print_strU0("1");uart_send(Zone1_Prev);
        break;
     
       case 0x32: 
          if(Door_V == Door_closed ) {   Zone2_Prev = Door_closed; Zone2_Status = 0; }
          else if(Door_V == Door_Open ){ Zone2_Prev = Door_Open;   Zone2_Status = 1; }
          data_EEPROM[1] = Zone2_Prev;
          print_strU0("2");uart_send(Zone2_Prev);
          EEPROM.write(301, Zone2_Prev );
         break;
       case 0x33: 
          if(Door_V == Door_closed ) {   Zone3_Prev = Door_closed; Zone3_Status = 0; }
          else if(Door_V == Door_Open ){ Zone3_Prev = Door_Open;   Zone3_Status = 1; }
          data_EEPROM[2] = Zone3_Prev; print_strU0("3");uart_send(Zone3_Prev);
          EEPROM.write(302, Zone3_Prev );
         break;
         
       case 0x34: 
          if(Door_V == Door_closed ) {   Zone4_Prev = Door_closed; Zone4_Status = 0; }
          else if(Door_V == Door_Open ){ Zone4_Prev = Door_Open;   Zone4_Status = 1; }
          data_EEPROM[3] = Zone4_Prev; print_strU0("4");uart_send(Zone4_Prev);
          EEPROM.write(303, Zone4_Prev );
        break;
      case 0x35: 
          if(Door_V == Door_closed ) {   Zone5_Prev = Door_closed; Zone5_Status = 0; }
          else if(Door_V== Door_Open ){ Zone5_Prev = Door_Open;   Zone5_Status = 1; }
          data_EEPROM[4] = Zone5_Prev; print_strU0("5");uart_send(Zone5_Prev);
          EEPROM.write(304, Zone5_Prev );
        break;
     case 0x36: 
          if(Door_V == Door_closed ) {   Zone6_Prev = Door_closed; Zone6_Status = 0; }
          else if(Door_V== Door_Open ){ Zone6_Prev = Door_Open;   Zone6_Status = 1; }
          data_EEPROM[5] = Zone6_Prev; print_strU0("6");uart_send(Zone6_Prev);
          EEPROM.write(305, Zone6_Prev );
        break;
     case 0x37: 
          if(Door_V == Door_closed ) {   Zone7_Prev = Door_closed; Zone7_Status = 0; }
          else if(Door_V == Door_Open ){ Zone7_Prev = Door_Open;   Zone7_Status = 1; }
          data_EEPROM[6] = Zone7_Prev; print_strU0("7");uart_send(Zone7_Prev);
          EEPROM.write(306, Zone7_Prev );
        break;
     case 0x38: 
          if(Door_V == Door_closed ) {   Zone8_Prev = Door_closed; Zone8_Status = 0; }
          else if(Door_V == Door_Open ){ Zone8_Prev = Door_Open;   Zone8_Status = 1; }
          data_EEPROM[7] = Zone8_Prev; print_strU0("8");uart_send(Zone8_Prev);
          EEPROM.write(307, Zone8_Prev );
        break;
     
   } //Debug_Ms =0x39;

}
