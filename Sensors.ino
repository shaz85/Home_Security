char Alarm=0;

void Battery_Voltage(void){
 
}

 unsigned char message_send_zones=0;
unsigned char stability_sensor_cnt = 60;
unsigned char zone1_alert_send = 0, zone2_alert_send = 0, zone3_alert_send = 0, zone4_alert_send = 0;
  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
void sensors_status_check(void){
    // Fire_sensor();
  static unsigned char sendDebug=0xFF;
  if(System_Enable_Disable == 0x31 ){      
    /*
      ---------------------- First Door Sensor ------------
    */
    if(Sensor_1E == 0x31 && zone1_up_debounce > stability_sensor_cnt && digitalRead(ZONE1_PIN)){
      zone1_up_debounce = stability_sensor_cnt;
      zone1_down_debounce = 0;     

      if(zone1_in_alert && zone1_alert_send){  
        zone1_in_alert = 0; print_strU0("Door1 open \r\n");  
        Send_SMS_AlertsP2(1); Zone1_Status=0; if(call_ED== Enable) Security_call();
        zone1_in_alert = 1; zone1_alert_send =0;
      }
    }

    else if( zone1_down_debounce > stability_sensor_cnt && !(digitalRead(ZONE1_PIN)) ){        
      zone1_down_debounce = stability_sensor_cnt ;
      if(!zone1_alert_send) print_strU0(" Door1 close\r");     
      zone1_up_debounce = 0;  zone1_alert_send = 1;      
    }
    /*
        ---------------------- Second Door Sensor ------------
    */

    if(Sensor_2E == 0x31 && zone2_up_debounce > stability_sensor_cnt && digitalRead(ZONE2_PIN)){
      zone2_up_debounce = stability_sensor_cnt;
      zone2_down_debounce = 0;
      if(zone2_in_alert && zone1_alert_send){  
        zone2_in_alert = 0; print_strU0("Door2 open \r\n");   
        Send_SMS_AlertsP2(2); Zone2_Status=0; if(call_ED== Enable) Security_call();
        zone2_in_alert = 1; zone2_alert_send =0;               
      }
    }

    else if( zone2_down_debounce > stability_sensor_cnt && !(digitalRead(ZONE2_PIN)) ){        
      zone2_down_debounce = stability_sensor_cnt ;
      if(!zone2_alert_send) print_strU0(" Door2 close\r");
      zone2_up_debounce = 0;  zone2_alert_send = 1;             
    }

    /*
        ---------------------- Third Door Sensor ------------
    */

    if(Sensor_3E == 0x31 && zone3_up_debounce > stability_sensor_cnt && digitalRead(ZONE3_PIN)){
      zone3_up_debounce = stability_sensor_cnt;
      zone3_down_debounce = 0;
      if(zone3_in_alert && zone1_alert_send){  
        zone3_in_alert = 0; print_strU0("Door3 open \r\n"); 
        Send_SMS_AlertsP2(2); Zone3_Status=0; if(call_ED== Enable) Security_call();
        zone3_in_alert = 1; zone3_alert_send =0;              
      }
    }

    else if( zone3_down_debounce > stability_sensor_cnt && !(digitalRead(ZONE3_PIN)) ){        
      zone3_down_debounce = stability_sensor_cnt ;
      if(!zone3_alert_send) print_strU0(" Door3 close\r");      
      zone3_up_debounce = 0;  zone3_alert_send = 1;          
    }
    /*
        ---------------------- Fourth Door Sensor ------------
    */
    if(Sensor_4E == 0x31 && zone4_up_debounce > stability_sensor_cnt && digitalRead(ZONE4_PIN)){
      zone4_up_debounce = stability_sensor_cnt;
      zone4_down_debounce = 0;
      if(zone4_in_alert && zone4_alert_send){
        zone4_in_alert = 0;print_strU0("Door4 open \r\n");
        Send_SMS_AlertsP2(2); Zone4_Status=0; if(call_ED== Enable) Security_call();
        zone4_in_alert = 1; zone4_alert_send =0;
      }
    }

    else if( zone4_down_debounce > stability_sensor_cnt && !(digitalRead(ZONE4_PIN)) ){        
      zone4_down_debounce = stability_sensor_cnt ; 
      if(!zone4_alert_send) print_strU0(" Door4 close\r");     
      zone4_up_debounce = 0;  zone4_alert_send = 1;
    }
  
  }
  else {
         // digitalWrite(Buzzer_ON_1, LOW); Alarm = 0;digitalWrite(Red_led, LOW);
      
     }

}


  //**************************************************************//
 //********************* Motion_and_Smoke  **********************//
//**************************************************************//
char alarm_Zone=0;
void Fire_sensor(void){
       //************************* Zone 1 on fire check ***********************//
            
}


