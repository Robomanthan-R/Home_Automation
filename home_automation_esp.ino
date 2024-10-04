char x ;
#include "BluetoothSerial.h"

#include <esp_now.h>
//#include <WiFi.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is off please turn on
#endif
BluetoothSerial SerialBT;
int led =2;
int fan = 4;
int led2 = 12;
int led3 = 14;
int led4 = 13;
int led5 = 27;
int led6 = 15;
int led7 = 5;

void setup ()
{ 
  Serial.begin(115200);
  SerialBT.begin("Robomanthan_Amrendra"); //Bluetooth device name
  Serial.println("Now Our Homeautomation device active , you can pair with Bluetooth");
  pinMode(led,OUTPUT);
   pinMode(fan,OUTPUT);
    pinMode(led2, OUTPUT);
     pinMode(led3, OUTPUT);
      pinMode(led4, OUTPUT);
       pinMode(led5, OUTPUT);
        pinMode(led6, OUTPUT);
         pinMode(led7, OUTPUT);
}
void loop()
{ 
  if (SerialBT.available())
  {
    x = SerialBT.read();
    Serial.println(x);

    if (x=='a')
    {
    digitalWrite(led,1);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("light 1 on");
    }
    if (x=='b')
    {
    digitalWrite(led,0);
    digitalWrite(fan,1);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Fan on");
  }
   if (x =='c')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,1);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 2 on");
   }
   if (x =='d')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,1);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 3 on");
   }
   if (x =='e')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,1);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 4 on");
   }
   if (x =='f')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,1);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 5 on");
   }
   if (x =='g')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,1);
    digitalWrite(led7,0);
    Serial.println("Light 6 on");
   }
   if (x =='h')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,1);
    Serial.println("Light 7 on");
   }
    if (x=='A')
    {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("light 1 off");
    }
    if (x=='B')
    {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Fan off");
  }
   if (x =='C')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 2 off");
   }
   if (x =='D')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 3 off");
   }
   if (x =='E')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 4 off");
   }
   if (x =='F')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 5 off");
   }
   if (x =='G')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 6 off");
   }
   if (x =='H')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("Light 7 off");
   }
   if (x=='t')
   {
    digitalWrite(led,1);
    digitalWrite(fan,1);
    digitalWrite(led2,1);
    digitalWrite(led3,1);
    digitalWrite(led4,1);
    digitalWrite(led5,1);
    digitalWrite(led6,1);
    digitalWrite(led7,1);
    Serial.println("All on");
   }
   if (x=='T')
   {
    digitalWrite(led,0);
    digitalWrite(fan,0);
    digitalWrite(led2,0);
    digitalWrite(led3,0);
    digitalWrite(led4,0);
    digitalWrite(led5,0);
    digitalWrite(led6,0);
    digitalWrite(led7,0);
    Serial.println("All off");
   }  
    }}