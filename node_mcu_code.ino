#include <SoftwareSerial.h>//imported library for serial communication
#include<ArduinoJson.h>// imported json lib to send multiple data to node mcu
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>//library for blynk app
SoftwareSerial s(D6,D5);//

char auth[] = "Auth-code";//given when we create project in blynk app

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "username";
char pass[] = "Wifi-password";

float data1;
float data2;
BlynkTimer timer;


void myTimerEvent()
{
  float voltage = data1*5/1023;  
  float adcvoltage=data2*5/1023;
  float current=(adcvoltage-2.5)/0.1;    //Divided by 0.1 as i used 20A current sensor, if we used 30A we would have divided by 0.66, this is sensitivity
  float power=voltage*current;
  Blynk.virtualWrite(V5, voltage);  //sending data to users' blynk app
  Blynk.virtualWrite(V6, current);  //over virtual pins,V5 V6 V7
  Blynk.virtualWrite(V7, power);
}
void setup() {
s.begin(9600);
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
 

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

 
void loop() {
  StaticJsonBuffer<100> jsonBuffer;// created the jsonbuffer 
  JsonObject& root = jsonBuffer.parseObject(s); // read the JSON string the serial port and store it in a JsonObject
 if (root == JsonObject::invalid())
    return;
  data1=root["voltage"];
  data2=root["current"];

 Blynk.run();
 timer.run();
 
}
