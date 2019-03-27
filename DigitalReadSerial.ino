#include <Servo.h>
// 
int leftDistSPint, rightDistSPin, frontDistSPin, poten, fanPin, pingSPin, bottomLineSPin, servoLeftPos, servoRightPos;
int fireSPin = 3;
Servo servoLeft, servoRight;
int stop = 90;
int fireState;
int fLeft= 180;
int fRight= 0;
int threshold = 200;              // distance threshold for sensors to tell how to navigate
int valLeft = 0;                  // variable to store the values from LEFT sensor(initially zero)
int valRight = 0;                 // variable to store the values from RIGHT sensor(initially zero)
int valForward = 0;               // variable to store the values from FORWARD sensor(initially zero)
int onLine = 0;
//right distance has min 132 max 768
//front distance mins 132 andmax 767
//left distance min 112 and max 767
//line sensor min 16 and max is 1023
//fire has max of 985

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(fanPin, OUTPUT);
  //setup movement servos
  servoLeft.attach();
  servoRight.attach();
  servoLeft.write(90);
  servoRight.write(90);
}


// the loop routine runs over and over again forever:
void loop() 
{
  // check for fire sensor active:
  readSensor()// possibly want a read sensor method that takes a reading of all sensors readSensor()
  
  delay(1);        // delay in between reads for stability
  
  if(bottomLineSPin>50 && fireState){
    //stop moving
      
    //aim
    digitalWrite(fanPin);
    
  }
  
  else if(!fireState)
  {
    leftHandWallFollow();
  }
    
  
  void leftHandWallFollow()
  {
    readSensor();
    
    if(valLeft > threshold && valRight > threshold && valFront < threshold) //2 way intersection
    {
      turnLeft();
    }
    
    else if(valLeft < threshold && valRight < threshold && (valFront > threshold) ) // empty space
    { 
        forward();//Moves straight                                                                                      
    }
    
    else if(valLeft < threshold && valRight < threshold && valForward < threshold)
    {
      backup();
      turnaround();
    }
    
    else if(valLeft > threshold) 
    {
      turnLeft(); // ???need to add amount of time to turn for???
    }
    
    else if(valLeft < threshold && valFront <threshold && valRight > threshold)
    {
      turnRight();
    }
    
  }
  
  void stop()
  {
    servoLeft.write(90);
    servoRight.write(90);
  }
  
  void forward()
  {
    servoLeft.write(fLeft);
    servoRight.write(fRight);
  }
  void backward()
  {
    servoLeft.write(leftBackward);
    servoRight.write(rightBackward);
  }
  void turnLeft()
  {
    servoLeft.write(stop);
    servoRight.write(rightForward);
  }
  void turnRight()
  {
    servoLeft.write(fLeft));
    servoRight.write(stop);
  }
  void turnAround()
  {
    servoLeft.write(fLeft);
    servoRight.write(fLeft);
  }
  void readSensors()
  {
    valLeft = digitalRead(leftDistancePin);
    valRight = digitalRead(rightDistancePin);
    valFront = digitalRead(frontDistancePin);
    fireState = digitalRead(firePin);
  }
  
}




