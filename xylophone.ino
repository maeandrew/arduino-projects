#include <Stepper.h>
#include <Servo.h> 

const int stepsPerRevolution = 200;  //EM34
//black+white - ground, 3,4,5,6
Stepper myStepper(stepsPerRevolution, 8,9,10,11);    

Servo myServo;

int curent_step = 0;   

//calibration
//int length = 16;
//char notes[] = "cdefgabCCbagfedc";
//int beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//jingle_bells
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};


int tempo = 100;
int stepper_speed = 40;
 
void setup() {
  Serial.begin(9600);  
  myStepper.setSpeed(stepper_speed);  //max for  EM34  
  
  myServo.attach(2);
  
  intro();
   
}

void intro() {
  
  myServo.write(90);
  delay(300);   
  myServo.write(45);
  delay(300);   
  myServo.write(90);
  delay(300);   
  myServo.write(45);
  
  delay(500);
    
  
  delay(200);  
  myServo.write(14);
  delay(500);  
  myStepper.step(35);  
  myStepper.step(-35);  
  delay(500);  
  
  myServo.write(20);    
  delay(500);   
}

void loop() {
    
   for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
      
      // pause between notes
      delay(tempo / 2); 
  }
  
  delay(5000);
     
}


void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(i, duration);
    }
  }
}

void playTone(int tone, int duration){  
  int step = 0;
  int move_duration = 0;
  int old_step = curent_step;
  switch (tone) {
    case 0:
      step = -curent_step + 0;
      curent_step = 0;
      break;
    case 1:
      step = -curent_step + 6;
      curent_step = 6;
      break;
    case 2:
      step = -curent_step + 11;
      curent_step = 11;
      break;  
    case 3:
      step = -curent_step + 15;
      curent_step = 15;
      break;
    case 4:
      step = -curent_step + 19;
      curent_step = 19;
      break;
    case 5:
      step = -curent_step + 24;
      curent_step = 24;
      break; 
    case 6:
      step = -curent_step + 29;
      curent_step = 29;
      break;
    case 7:
      step = -curent_step + 35;                 
      curent_step = 35;
      break; 
    default: 
    break;
  }
  myStepper.step(step);  
  kick();  
  
  move_duration = calcTimeForMoving(old_step, curent_step);
  
  Serial.print(duration);
  Serial.print(' ');
  Serial.println(move_duration);
  
  delay(duration);
}

int calcTimeForMoving(int curent_step, int step){    
  int move_duration = 0;
  if(step >= curent_step){
    move_duration = (step - curent_step) * stepper_speed;
  } else {
    move_duration = (curent_step - step) * stepper_speed;
  }
  return move_duration / 10;
}

void kick(){    
  delay(100);  
  myServo.write(14);
  delay(50);
  myServo.write(20);  
  delay(100);
}
