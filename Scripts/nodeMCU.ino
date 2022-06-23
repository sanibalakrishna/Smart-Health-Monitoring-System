#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include<SoftwareSerial.h>

SoftwareSerial NodeMCU_SoftSerial(D1,D2);
char c;
String s,datain;
String data1,data2,data3,data4;
int8_t indexOfA,indexOfB,indexOfC,indexOfD;

const char*  ssid = "jay"; //Your Network SSID
const char* password = "12345678"; //Your Network Password


WiFiClient client;

unsigned long myChannelNumber = 1686722 ; //Your Channel Number (Without Brackets)
const char* myWriteAPIKey = "QW71ADUCTW472GRZ"; //Your Write API Key

void setup()
{
 Serial.begin(57600);
 NodeMCU_SoftSerial.begin(9600);
 
 
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}



void loop() {
 
  // put your main code here, to run repeatedly:
  while(NodeMCU_SoftSerial.available()>0)
  {
    c=NodeMCU_SoftSerial.read();
    if(c=='\n')
    {
      break; 
    }
    else
    {
      datain+=c;
    }
  }
  if(c=='\n')
  {
    getdata();
    Serial.print("data1="+data1);
    ThingSpeak.setField( 1,data1);
    Serial.print("data2="+data2);
    ThingSpeak.setField( 2,data2);
    Serial.print("data3="+data3);
    ThingSpeak.setField( 3,data3);
    Serial.println("data4="+data4);
    ThingSpeak.setField( 4,data3);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    c=0;
    datain="";
    }
    delay(1);
  
}

void getdata()
{
  indexOfA=datain.indexOf("A");
  indexOfB=datain.indexOf("B");
  indexOfC=datain.indexOf("C");
  indexOfD=datain.indexOf("D");
  data1=datain.substring(0,indexOfA);
  data2=datain.substring(indexOfA+1,indexOfB);
  data3=datain.substring(indexOfB+1,indexOfC);
  data4=datain.substring(indexOfC+1,indexOfD);
} 
