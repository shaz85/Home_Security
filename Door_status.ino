  //**************************************************************//
 //******************** Door_Sensor_Status  *********************//
//**************************************************************// 
void Door_Sensor_Status(unsigned char mode){
         int i;        
  for(i=300;i<325;i++){
     data_EEPROM[i-300] = EEPROM.read(i);
     
     }
     if(mode == 1){
         if(data_EEPROM[0] == Door_closed | data_EEPROM[0] == Door_Open ){ Zone1_Prev = data_EEPROM[0]; }
         if(data_EEPROM[1] == Door_closed | data_EEPROM[1] == Door_Open ){ Zone2_Prev = data_EEPROM[1];}
         if(data_EEPROM[2] == Door_closed | data_EEPROM[2] == Door_Open ){ Zone3_Prev = data_EEPROM[2]; }
         if(data_EEPROM[3] == Door_closed | data_EEPROM[3] == Door_Open ){ Zone4_Prev = data_EEPROM[3]; }
         
         if(data_EEPROM[4] == Door_closed | data_EEPROM[4] == Door_Open ){ Zone5_Prev = data_EEPROM[4]; }
         if(data_EEPROM[5] == Door_closed | data_EEPROM[5] == Door_Open ) Zone6_Prev = data_EEPROM[5];
         if(data_EEPROM[6] == Door_closed | data_EEPROM[6] == Door_Open ) Zone7_Prev = data_EEPROM[6];
         if(data_EEPROM[7] == Door_closed | data_EEPROM[7] == Door_Open ) Zone8_Prev = data_EEPROM[7];
     }
    else if (mode == 2){
         if(data_EEPROM[0] == Door_closed ) Zone1_Status = 0; else Zone1_Status = 1;
         if(data_EEPROM[1] == Door_closed ) Zone2_Status = 0; else Zone2_Status = 1;
         if(data_EEPROM[2] == Door_closed ) Zone3_Status = 0; else Zone3_Status = 1;
         if(data_EEPROM[3] == Door_closed ) Zone4_Status = 0; else Zone4_Status = 1;
        
         if(data_EEPROM[4] == Door_closed ) Zone5_Status = 0; else Zone5_Status = 1;
         if(data_EEPROM[5] == Door_closed ) Zone6_Status = 0; else Zone6_Status = 1;
         if(data_EEPROM[6] == Door_closed ) Zone7_Status = 0; else Zone7_Status = 1;
         if(data_EEPROM[7] == Door_closed ) Zone8_Status = 0; else Zone8_Status = 1;
    }  
}
