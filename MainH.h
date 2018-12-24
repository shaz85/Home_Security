/**
  ******************************************************************************
  * @file    MainH.h
  * @author  Muhammad Shahzad   itzshahzad@gmail.com
  * @version V1.0
  * @date    18-Dec-2018
  * @brief   Main Header File
  ******************************************************************************
  The file include bit decleration prototype of funcitons and Golbal variable
  ******************************************************************************
  */




char AT_cmd[6]="AT\r";
char get_strUart2[30], get_strUart2Cnt=0;

unsigned char Zone1_Prev=200, Zone2_Prev=200, Zone3_Prev=200, Zone4_Prev=200;
unsigned char Zone5_Prev=200, Zone6_Prev=200, Zone7_Prev=200, Zone8_Prev=200;

char Zone1_Status = 0, Zone2_Status = 0, Zone3_Status = 0, Zone4_Status = 0;
char Zone5_Status = 0, Zone6_Status = 0, Zone7_Status = 0, Zone8_Status = 0;

char  str_clearF=0;
unsigned char Door_closed=0x30,
              Door_Open=0x31;
char Open_str[11]=" is opened", Colse_str[11]=" is closed";
char Door_str[6] = "Door ";

int len; 
unsigned char read_d;
unsigned int one_sec=0;

char one='1', two='2', three='3',four='4', five='5', six='6', seven='7', eight='8', nine='9', zero='0';
void initlization(void);
char Store_str[10] = "Room ";

unsigned char Alarm_Enb_Dis=255,Touch_1Sec=0;