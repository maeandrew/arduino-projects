#include <Wire.h>
#include "RTClib.h"
#include <SD.h>

RTC_DS1307 RTC;
// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;
const byte motionPin = 2;
byte senseMotion = 0;

void setup () {
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
  

    if (! RTC.isrunning()) {
      Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      RTC.adjust(DateTime(__DATE__, __TIME__));
    }
  
    
    // make sure that the default chip select pin is set to
    // output, even if you don't use it:
    pinMode(10, OUTPUT);
    pinMode(motionPin, INPUT);
      
      // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
      Serial.println("Card failed, or not present");
      // don't do anything more:
      return;
    }
}

void loop () {
  
    int senseMotion = digitalRead(motionPin);
  
    if(senseMotion == HIGH){
      
      DateTime now = RTC.now();
     
      File dataFile = SD.open(now.year() + "-" + now.month() + "-" + now.day() + ".log", FILE_WRITE);
      
      if (dataFile) {
                          
        String dataString = "";
     
        dataString += now.year();
        dataString += '/';
        dataString += now.month();
        dataString += '/';
        dataString += now.day();
        dataString += ' ';
        dataString += now.hour();
        dataString += ':';
        dataString += now.minute();
        dataString += ':';
        dataString += now.second();
        dataString += " Moution detected!";
        
        dataFile.println(dataString);
        dataFile.close();
        
        Serial.println(dataString);
  
      }  
  
    }
    
    
   
    delay(1000);
}
