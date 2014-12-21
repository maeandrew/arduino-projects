int calibrationTime = 10;
int Time = 0;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockinHigh = false;
int LEDsop = 13; // pin 13 includes resistor sop- signal out pin
int outpin1 = 11; // for any other device that doesn't require resistor
int outpin2 = 12; // for any other device that doesn't require resistor
int SensorInpin = 2; // can vary, must be digital from 1-12
boolean sensorready = false;
void setup () {
    pinMode(LEDsop, OUTPUT);
    digitalWrite(LEDsop, LOW);
    
    pinMode(outpin1, OUTPUT);
    digitalWrite(outpin1, LOW);
    
    pinMode(outpin2, OUTPUT);
    digitalWrite(outpin2, LOW);
    
    pinMode(SensorInpin, INPUT);   
    do {
        digitalWrite(LEDsop, HIGH);
        delay(500);
        digitalWrite(LEDsop, LOW);
        delay(500);
        Time = Time + 1;
    } while (Time < calibrationTime);
    digitalWrite(LEDsop, LOW); //if led turns off, sensor is ready
    sensorready = true;
}
void loop () {
    if (sensorready == true) {
        if (digitalRead(SensorInpin)) {
            digitalWrite(LEDsop, HIGH);
            digitalWrite(outpin1, HIGH);
            digitalWrite(outpin2, HIGH);
            delay(7000); //modify to meet your required delay time
            
            digitalWrite(LEDsop, LOW);
            digitalWrite(outpin1, LOW);
            digitalWrite(outpin2, LOW);            
            delay(250);
        }
    }
}
