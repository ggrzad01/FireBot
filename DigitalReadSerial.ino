#include <Servo.h>
// 
int leftDistSPint, rightDistSPin, frontDistSPin, poten, fanPin, pingSPin, bottomLineSPin, servoLeftPos, servoRightPos;
int fireSPin = 3;
Servo servoLeft, servoRight;
int fLeft=1;
int fRight= -1 * fLeft;
int threshold = 200;              // distance threshold for sensors to tell how to navigate
int valLeft = 0;                  // variable to store the values from LEFT sensor(initially zero)
int valRight = 0;                 // variable to store the values from RIGHT sensor(initially zero)
int valForward = 0;               // variable to store the values from FORWARD sensor(initially zero)
int onLine = 0;


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
  // possibly want a read sensor method that takes a reading of all sensors readSensor()
  int fireState = digitalRead(fireSensorPin);
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
    servoLeft.write(180);
    servoRight.write(180);
  }
  void backward()
  {
    servoLeft.write(0);
    servoRight.write(0);
  }
  void turnLeft()
  {
    servoLeft.write(90);
    servoRight.write(180);
  }
  void turnRight()
  {
    servoLeft.write(180);
    servoRight.write(90);
  }
  void readSensors()
  {
    valLeft = digitalRead(leftDistancePin);
    valRight = digitalRead(rightDistancePin);
    valFront = digitalRead(frontDistancePin);
    fireState = digitalRead(firePin);
  }
  
}




