#include <SoftwareSerial.h> //imported library for serial communication
#include<ArduinoJson.h> // imported json lib to send multiple data to node mcu
SoftwareSerial s(5,6);//we shall consider pin 5 as Rx and pin 6 as Tx
 
void setup() {
s.begin(9600);//To begin the serial communication between Arduino and NodeMCU with 9600 bits per second
}
 
void loop() {

 StaticJsonBuffer<100> jsonBuffer;
 JsonObject& root=jsonBuffer.createObject();
 root["voltage"] =analogRead(A0);
 root["current"]=analogRead(A1);
if(s.available()>0)
{
  root.printTo(s);//To print the JsonObject to the serial port
}
delay(100);
}
