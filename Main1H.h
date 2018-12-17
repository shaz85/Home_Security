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



//char Door


char Turn_OFF_Buzzer=0x31;
char Mode = 0x30;
char Debug_Ms = 0x31;

#define ZONE1_PIN 2
#define ZONE2_PIN 3
#define ZONE3_PIN 7
#define ZONE4_PIN 12


unsigned int zone1_up_debounce = 0 , zone2_up_debounce = 0 , zone3_up_debounce = 0, zone4_up_debounce = 0;
unsigned int zone1_down_debounce = 0 , zone2_down_debounce = 0 , zone3_down_debounce = 0, zone4_down_debounce = 0;

unsigned char zone1_in_alert=1, zone2_in_alert=1, zone3_in_alert=1, zone4_in_alert=1;
int ZoneFire_CntSet=200;
int zone_FireTH=600;

int call_ED=0x30,SMS_RepetationT=1;

unsigned char Zone1_Rep = 1 , Zone2_Rep = 1 , Zone3_Rep = 1 ,Zone4_Rep = 1 ;
unsigned char Zone5_Rep = 1 , Zone6_Rep = 1 , Zone7_Rep = 1 ,Zone8_Rep = 1 ;

char PhoneNOList[5][15];
char System_Enable_Disable  =0x30;

//char DynamicIP[40];
char IMEI[3]="12";
char datastr[100];
int dat_cnt=0;

char Enab = 0x31;

char ATCMGF[12]="AT+CMGF=1\r";
char ATCMGS[10]="AT+CMGS=";

char Password[7]="Mega>",Master[15]="+923347455997";
char Master1[15]="+923096891878";
char M_Recv_numb[15];
char CTRL_Z=26;
char Volt_Var[7];
 
 //Init923347455997,+923059784266,+923347455997,+923096891878,,
int Packet_Send_Time=60;


const int GSM_Reboot_Pin =  9;
char gsm_data[250]; 
int recv_cnt=0;
char saved_EppromV=0;
unsigned char data_EEPROM[30];
char Comma1 =',';

char GPRS_EN_Dis=0x30;
char Global_Alerts_ED=0x31;

unsigned char pg_send=0;

char Server_connet=0;



char ATCMGL_ALL[]="AT+CMGL=\"ALL\"\r";
char Ring[5]="RING";
char ERROR1[6]="ERROR";

unsigned char csc_cnt=0;
char *res,txt22[4],Message[150],MesG_RR=0,prv;
char Error_cnt=0;
unsigned int Message_cnt;

char Sensor_1E  = 49, Sensor_2E  = 49, Sensor_3E  = 49, Sensor_4E  = 49, Sensor_5E  = 49, Sensor_6E  = 49, Sensor_7E  = 49;
char Sensor_8E  = 49, Sensor_9E  = 49, Sensor_10E = 49;
unsigned char    Enable = 0x31, Disable = 0x30,Read;
//int Zone_1Sensor,Zone_2Sensor,Zone_3Sensor,Zone_4Sensor;
int Zone_TH = 500;


void Sensor_Enable_disble(unsigned char);
char gsm_No_Reply=0;


int AT_check=0;

 //*************************************************************//
//**************************************************************//
String pasword = String("Mega");


String Byte12_str;
char Array12B[12];
unsigned char important_Message=0;

char COMMA[]=",";
//char GSM_signal_str[5]="31";
unsigned int Repeat_SMS_Reply=70;
char pV=0;
 //*************************************************************//
//**************************************************************//

const char ATCSCS[] PROGMEM  = {"AT+CSCS=\"GSM\"\r"};
const char SystemEn[] PROGMEM  = {"The System is enabled \r"};
const char SystemEnDis[] PROGMEM  = {"The System is disabled \r"};
const char Call_ED[] PROGMEM  = {"Call E/D Repetation "};
const char SysAlerts[] PROGMEM  = {"System Alerts = "};
const char Reboot[] PROGMEM  = {"Reboot"};
const char DoorOpen[] PROGMEM  = {"The following doors still open"};
const char ATQMGDA[] PROGMEM  = {"\rAT+CMGDA=\"DEL ALL\"\r"};

const char ATQMGFZ[] PROGMEM  = {"\rAT+CMGF=0\r"};

const char ATQMGDAS[] PROGMEM  = {"\rAT+QMGDA=6\r"};
const char ATCPMS[] PROGMEM  = {"AT+CPMS=\"SM\",\"SM\",\"SM\"\r"};

const char GSMReboot[] PROGMEM  = {"GSM Reboot"};
const char SystemReboot[] PROGMEM  = {"System Reboot"};
const char Debugenb[] PROGMEM  = {"Debug enb\r"};
const char ATIPR[] PROGMEM  = {"AT+IPR=9600\r"}; 
const char ATE0[] PROGMEM  = {"ATE0\r"}; 
const char ATW[] PROGMEM  = {"AT&W\r"}; 
const char Sens_EnaArr[] PROGMEM = {"Sensor Enable or disable\r"};
const char thisNumber[] PROGMEM = {"by this number\r"};
//String inputString = "";         // a string to hold incoming data





