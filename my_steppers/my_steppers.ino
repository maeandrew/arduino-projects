#include <Stepper.h>

//const int stepsPerRevolution = 200;  //EM34
//білий+чорний - земля, далі по черзі

//const int stepsPerRevolution = 50;  //42
//2 білих - земля, зелений,червоний,жовтий,синій

const int stepsPerRevolution = 50;  //EPOCH
//Червоний- земля, жовтий,рожевий,зелений,чорний

Stepper myStepper(stepsPerRevolution, 8,9,10,11);     



void setup() {
  Serial.begin(9600);
}

void loop() {
//  myStepper.setSpeed(160);  //max for  EM34
  myStepper.setSpeed(50); //max for 42
 
  myStepper.step(stepsPerRevolution);
  delay(500);
  myStepper.step(-stepsPerRevolution);
  delay(500);
  
 
}

