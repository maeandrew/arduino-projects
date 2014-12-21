 
int redPin = 5;
int greenPin = 6;
int bluePin = 3;
 
int lightDelay = 1000;
int pauseDelay = 0;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()
{  
  setColor(255, 255, 255);  // white
  delay(lightDelay);
  setColor(0, 0, 0);  // pause
  delay(pauseDelay);
  
  setColor(255, 0, 0);  // red
  delay(lightDelay);
  setColor(0, 0, 0);  // pause
  delay(pauseDelay);
  
  setColor(0, 255, 0);  // green
  delay(lightDelay);
  setColor(0, 0, 0);  // pause
  delay(pauseDelay);
  
  setColor(0, 0, 255);  // blue
  delay(lightDelay);
  setColor(0, 0, 0);  // pause
  delay(pauseDelay);
  
  setColor(255, 255, 0);  // yellow
  delay(lightDelay);  
  setColor(0, 0, 0);  // pause
  delay(pauseDelay);
  
  setColor(80, 0, 80);  // purple
  delay(lightDelay);
  setColor(0, 0, 0);  // pause
  delay(pauseDelay);
  
  setColor(0, 255, 255);  // aqua
  delay(lightDelay);
  setColor(0, 0, 0);  // pause
  delay(pauseDelay);

}
 
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
