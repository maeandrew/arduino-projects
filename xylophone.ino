/**
  Alpha version of xylophone
  1) arduino
  2) breadboard shield
  3) Transistors *4
  4) 1 kOm resistors *4
  5) Stepper motor
  6) Servo motor
  7) Сhildren's xylophone
  
  Schematic diagram will be coming soon
  
  Video: https://www.youtube.com/watch?v=WzDKYsDgcLQ

*/

#include <Stepper.h>
#include <Servo.h> 

const int stepsPerRevolution = 200;  //EM34
//black+white - ground, 3,4,5,6
Stepper myStepper(stepsPerRevolution, 8,9,10,11);    

Servo myServo;

int curent_step = 0;   


//calibration

// Length must equal the total number of notes and spaces
int length0 = 16;

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)
char notes0[] = "cdefgabCCbagfedc";

// Beats is an array of values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.
int beats0[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//jingle_bells
int length1 = 26;
char notes1[] = "eeeeeeegcde fffffeeeeddedg";
int beats1[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

int length2 = 15; // the number of notes
char notes2[] = "ccggaagffeeddc "; // a space represents a rest
int beats2[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };

int length3 = 25; // the number of windy notes
char notes3[] = "gagfefgdefefggagfefgdgec "; // a space represents a rest
int beats3[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 4 };

int length4 = 32; // the number of rainy notes
char notes4[] = "geggegeggeggeaggegfedcdegfedcde ";
int beats4[] = { 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };

int length5 = 27; // the number of sunny notes
char notes5[] = "cccegecdddbagcccegecddgabbcc ";
int beats5[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 4 };


int length6 = 33; // the number of cloudy notes
char notes6[] = "cdeccdecefgefggagfecgagfecdgcdgc "; // a space represents a rest
int beats6[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 4, 2, 2, 4, 4 };

// solfeo Maria
int length7 = 29; // the number of notes
char notes7[] = "cccdefefgfedec cccdefefgfedc "; // a space represents a rest
int beats7[] = { 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1,  5 };

// solfeo estrella
int length8 = 50; // the number of notes
char notes8[] = "cccdefefgfedec cccdefefgfedc efgagfedec efgagfedc "; // a space represents a rest
int beats8[] = { 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,  3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5 };


int length9 = 18;
char notes9[] = "cdfda ag cdfdg gf ";
int beats9[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

int allLength[10] = {length1,length2,length3,length4,length5,length6,length7,length8,length9};
char *allNotes[10] = {notes1,notes2,notes3,notes4,notes5,notes6,notes7,notes8,notes9};
int *allBeats[10] = {beats1,beats2,beats3,beats4,beats5,beats6,beats7,beats8,beats9};

int tempo = 100;
int stepper_speed = 40;
 
void setup() {
  Serial.begin(9600);  
  myStepper.setSpeed(stepper_speed);  //max for  EM34  
  
  myServo.attach(2);
  
//  intro();
   
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
 
     
   for (int m = 0; m < sizeof(allLength); m++) {
     for (int i = 0; i < allLength[m]; i++) {
        if (allNotes[m][i] == ' ') {
          delay(allBeats[m][i] * tempo); // rest
        } else {
          playNote(allNotes[m][i], allBeats[m][i] * tempo);
        }
         Serial.print(m);
         Serial.print(' ');
         Serial.println(i);
        // pause between notes
        delay(tempo / 2); 
    }
    delay(2000);
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
     
  move_duration = calcTimeForMoving(old_step, curent_step);    
  delay(duration);
  
  myStepper.step(step);  
  kick(); 
  
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
