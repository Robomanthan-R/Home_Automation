char rx_byte  = 0;
char x ;
#include "BluetoothSerial.h"

#include <esp_now.h>
//#include <WiFi.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is off please turn on
#endif
BluetoothSerial SerialBT;
int led1=4;
int led2=2;
int Fan=18;
// int motor4=11;
void setup() {
  Serial.begin(9600);


pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(Fan,OUTPUT);
// pinMode(motor4,OUTPUT);
}
void loop() {
  if (Serial.available() > 0) {     
    rx_byte = Serial.read();  
    Serial.println(rx_byte);     
  
    // if ((rx_byte >= '1') && (rx_byte <= '9')) {
    //   Serial.print("Saurav: ");
    //   Serial.println(rx_byte);
    //   digitalWrite(led,1);
    //   delay(1500);
    // }
    if ((rx_byte == 'a')) {
      Serial.print("Led 2 On!! ");
      Serial.println(rx_byte);
      
      delay(500);
      digitalWrite(led1,0);
      digitalWrite(led2,1);
      digitalWrite(Fan,1);
    }
    if ((rx_byte == 'b')) {
      Serial.print("Led 1 On!!");
      Serial.println(rx_byte);
      
      digitalWrite(led1,1);
      digitalWrite(led2,0);
      digitalWrite(Fan,0);
      delay(500);
    }
     if ((rx_byte == 'c')) {
      Serial.print("Fan On!!");
      Serial.println(rx_byte);
      
      digitalWrite(led1,0);
      digitalWrite(led2,0);
      digitalWrite(Fan,1);
      delay(500);
    }
     if ((rx_byte == 'A')) {
      Serial.print("All components On!!");
      Serial.println(rx_byte);
      
      digitalWrite(led1,1);
      digitalWrite(led2,1);
      digitalWrite(Fan,1);
      delay(500);
    }
    if (rx_byte == 's'){
      Serial.println("All components off!!");
       digitalWrite(led1,0);
      digitalWrite(led2,0);
      digitalWrite(Fan,0);
      delay(500);
    
     }}}
