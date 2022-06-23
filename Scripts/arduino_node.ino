#include<SoftwareSerial.h>
#define USE_ARDUINO_INTERRUPTS true 
#include <PulseSensorPlayground.h> 
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

SoftwareSerial Arduino_SoftSerial(5,6);
int lm35=A0;
int data1,data2,data3,data4;

PulseOximeter pox;
 
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Arduino_SoftSerial.begin(9600);
  pinMode(10,INPUT);
  pinMode(11,INPUT);

   if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }  

  pox.setOnBeatDetectedCallback(onBeatDetected);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  pox.update();
  data1=tempfunc(lm35);
  data2=analogRead(A1);
   if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        data3=pox.getHeartRate();
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        data4=pox.getSpO2();
        Serial.println("%");
        Arduino_SoftSerial.print(data1);Arduino_SoftSerial.print("A");
        Arduino_SoftSerial.print(data2);Arduino_SoftSerial.print("B");
        Arduino_SoftSerial.print(data3);Arduino_SoftSerial.print("C");
        Arduino_SoftSerial.print(data4);Arduino_SoftSerial.print("D");
        Arduino_SoftSerial.print("\n");
 
        tsLastReport = millis();
    }
 
 
 
  
  
}
int tempfunc(int lm35)
{
  int tempadc=analogRead(lm35);
  float tempval=tempadc*4.88;
  int res=tempval/10;
  res-=70;
  return res;
}
