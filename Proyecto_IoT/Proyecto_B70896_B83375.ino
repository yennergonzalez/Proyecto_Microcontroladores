/*
   
   //Laboratorio de Microcontroladores
   //Proyecto 
   //Realizado por:
   //Gabriel Barahona Otoya B70896
   //Yenner Gonzalez Araya B83375
   
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "GalaxyA71"
#define REMOTEXY_WIFI_PASSWORD "GYPM9675"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "6d83ecce0edca93458833e1bb4587141"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 85 bytes
  { 255,0,0,18,0,78,0,16,179,1,129,0,4,5,57,5,1,83,101,110,
  115,111,114,101,115,32,100,101,32,71,97,115,47,72,117,109,111,0,129,0,
  5,69,55,6,1,83,101,110,115,111,114,101,115,32,100,101,32,70,108,97,
  109,97,0,68,19,3,15,57,41,8,36,135,94,65,112,38,79,13,13,65,
  112,12,79,13,13 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  float DatoHumo_var1;
  float DatoHumo_var2;
  float DatoHumo_var3;
  uint8_t led_2_r; // =0..255 LED Red brightness 
  uint8_t led_2_g; // =0..255 LED Green brightness 
  uint8_t led_2_b; // =0..255 LED Blue brightness 
  uint8_t led_1_r; // =0..255 LED Red brightness 
  uint8_t led_1_g; // =0..255 LED Green brightness 
  uint8_t led_1_b; // =0..255 LED Blue brightness 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

int SensorHG_1;
int SensorHG_2;
int SensorHG_3;
int SensorHG_1m;
int SensorHG_2m;
int SensorHG_3m;
int Buzzer = 22;
int SensorFlama_1 = 7;
int SensorFlama_2 = 5;
int SensorFlama_3 = 3;
int Flama_1; 
int Flama_2;
int Flama_3;

void setup() 
{
  RemoteXY_Init (); 
 
  pinMode(Buzzer, OUTPUT);
  pinMode(SensorFlama_1, INPUT);
  pinMode(SensorFlama_2, INPUT);
  pinMode(SensorFlama_3, INPUT);
  
}

void loop() 
{ 
  RemoteXY_Handler ();
   
  Flama_1 = digitalRead(SensorFlama_1);
  Flama_2 = digitalRead(SensorFlama_2);
  Flama_3 = digitalRead(SensorFlama_3);
  if (Flama_1 == LOW && Flama_2 == LOW && Flama_3 == LOW){
    digitalWrite(Buzzer, LOW);
    RemoteXY.led_1_r = 0;
    RemoteXY.led_1_g = 0;
    RemoteXY.led_1_b = 0;
    RemoteXY.led_2_r = 0;
    RemoteXY.led_2_g = 0;
    RemoteXY.led_2_b = 0;
  }
  else if (Flama_1 == HIGH){
    digitalWrite(Buzzer, HIGH);
    RemoteXY.led_1_r = 255;
    RemoteXY.led_1_g = 0;
    RemoteXY.led_1_b = 0;
  }
  else if (Flama_2 == HIGH){
    digitalWrite(Buzzer, HIGH);
    RemoteXY.led_2_r = 0;
    RemoteXY.led_2_g = 255;
    RemoteXY.led_2_b = 0;
  }
  else if (Flama_3 == HIGH){
    digitalWrite(Buzzer, HIGH);
    RemoteXY.led_2_r = 255;
    RemoteXY.led_2_g = 255;
    RemoteXY.led_2_b = 0;
  }
  
  SensorHG_1 = analogRead(A0);
  SensorHG_2 = analogRead(A1);
  SensorHG_3 = analogRead(A2);

  SensorHG_1m = map(SensorHG_1, 600, 820, 0, 100);
  SensorHG_2m = map(SensorHG_2, 140, 310, 0, 100);
  SensorHG_3m = map(SensorHG_3, 635, 820, 0, 100);

  if (SensorHG_1m < 0){
    RemoteXY.DatoHumo_var1 = 0;
  }
  if (SensorHG_1m > 100){
    RemoteXY.DatoHumo_var1 = 100;
  }
  if (SensorHG_2m < 0){
    RemoteXY.DatoHumo_var2 = 0;
  }
  if (SensorHG_2m > 100){
    RemoteXY.DatoHumo_var2 = 100;
  }
  if (SensorHG_3m < 0){
    RemoteXY.DatoHumo_var3 = 0;
  }
  if (SensorHG_3m > 100){
    RemoteXY.DatoHumo_var3 = 100;
  }
  if (SensorHG_1m > 0 && SensorHG_1m < 100){
    RemoteXY.DatoHumo_var1 = SensorHG_1m;
  }
  if (SensorHG_2m > 0 && SensorHG_2m < 100){
    RemoteXY.DatoHumo_var2 = SensorHG_2m;
  }
  if (SensorHG_3m > 0 && SensorHG_3m < 100){
    RemoteXY.DatoHumo_var3 = SensorHG_3m;
  } 
}
