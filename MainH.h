/**
  ******************************************************************************
  * @file    MainH.h
  * @author  Muhammad Shahzad
  * @version V1.0
  * @date    31-January-2014
  * @brief   Main Header File
  ******************************************************************************
  The file include bit decleration prototype of funcitons and Golbal variable
  ******************************************************************************
  */


#define DHTPIN 13 
#define S_SerialPin 2
 
 char Zone1_Pin = 0, Zone2_Pin = 1, Zone3_Pin = 2 ;
 char Zone4_Pin = 3, Zone5_Pin = 4, Zone6_Pin = 5 ;
 char Zone7_Pin = 6, Zone8_Pin = 7;
 char AT_cmd[6]="AT\r";
  char get_strUart2[30], get_strUart2Cnt=0;

  unsigned char Zone1_Prev=200, Zone2_Prev=200, Zone3_Prev=200, Zone4_Prev=200;
  unsigned char Zone5_Prev=200, Zone6_Prev=200, Zone7_Prev=200, Zone8_Prev=200;
 
 char Zone1_Status = 0, Zone2_Status = 0, Zone3_Status = 0, Zone4_Status = 0;
 char Zone5_Status = 0, Zone6_Status = 0, Zone7_Status = 0, Zone8_Status = 0;
 

 
char  str_clearF=0;
unsigned char Door_closed=0x30,Door_Open=0x31;
char Open_str[6]="Open", Colse_str[10]="Closed";
char Door_str[10] = " Door is ";

    char Buzzer_ON_1 = 21;
    char Buzzer_ON_2 =5;
    
    int Red_led = 34;
    int Green_led = 36;
    
    
    long All_Time=0, thisRUN_Time=0;
    long Temp;
    float bv_temp;
int len;    


    unsigned char read_d;
    unsigned int one_sec=0;

char one='1', two='2', three='3',four='4', five='5', six='6', seven='7', eight='8', nine='9', zero='0';
//Functions
unsigned char AthentcationSuc=0;
void initlization(void);
char Store_str[10] = "Room ";

unsigned char Alarm_Enb_Dis=255,Touch_1Sec=0;





unsigned char Alarm_Status=0;
char Mannual_Mute=1;
// Declare which fonts we will be using






int Sounder1_Relay1 = 4;
int Sounder2_Relay2 = 5;
char Relay_SMS = 0x30;
char Time_str[10]="Time : "; 
