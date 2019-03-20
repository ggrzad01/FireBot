#include <Servo.h>
// 
int leftDistSPint, rightDistSPin, frontDistSPin, poten, fanPin, pingSPin, bottomLineSPin, servoLeftPos, servoRightPos;
int fireSPin = 3;
Servo servoLeft, servoRight;
int fLeft=1;
int fRight= -1 * fLeft;

int onLine=0;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(fireSensorPin, INPUT);
  pinMode(rightDistSPin, INPUT);
  pinMode(leftDistSPin, INPUT);
  pinMode(pingSPin, INPUT);
  pinMode(frontDistSPin, INPUT);
  pinMode(poten, INPUT);
  pinMode(bottomLineSPin, INPUT);
  pinMode(fanPin, OUTPUT);
  servoLeft.attach();
  servoRight.attach();
}


// the loop routine runs over and over again forever:
void loop() 
{
  // check for fire sensor active:
  int fireState = digitalRead(fireSensorPin);
  delay(1);        // delay in between reads for stability

  
  
  if(bottomLineSPin>50 && fireState){
    //stop moving

    //change angle
  }
  
  else if(!fireState){
  
  //Left hand wall follow
    //sense wall
    
  //go forward
  
  //turn left

  //turn right 
  }
  
  }




