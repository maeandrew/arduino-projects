// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"
#include <SD.h>

#include <LiquidCrystal.h>

RTC_DS1307 RTC;

#define BUTTON_PIN  8

const int chipSelect = 4;
boolean buttonWasUp = true;  // была ли кнопка отпущена?
int spoonsCount = 0;  // была ли кнопка отпущена?


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup () {
    Serial.begin(57600);
    Wire.begin();
    RTC.begin();
    
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    lcd.begin(16, 2);

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  pinMode(10, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
      Serial.println("Card failed, or not present");
      // don't do anything more:
      return;
    }
  
}

void loop () {
  
    DateTime now = RTC.now();
    
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
    
      
    lcd.setCursor(0, 0);
    lcd.print(dataString);
    
  
  
    boolean buttonIsUp = digitalRead(BUTTON_PIN);
    
    Serial.println(buttonIsUp);
    
    if (buttonWasUp && !buttonIsUp) {
      delay(10);
      
      buttonIsUp = digitalRead(BUTTON_PIN);
      if (!buttonIsUp) {  
  
        spoonsCount++;      
        
        File dataFile = SD.open("food.log", FILE_WRITE);
        
        if (dataFile) {     
     
               
            lcd.setCursor(1, 0);
            lcd.print("L: ");
            lcd.print(spoonsCount);     
                      
            dataFile.print(dataString);          
            dataFile.print(" +1");          
            dataFile.println(spoonsCount);
            dataFile.close();      
          }    
         
       }
       
    }
    
    buttonWasUp = buttonIsUp;
   
    delay(1000);
    
}
