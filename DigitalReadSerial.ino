#include <Servo.h>
// 
int leftDistancePin = A2;
int rightDistancePin = A0;
int frontDistancePin = A1;
int bottomLineSPin = A3;
int poten, fanPin, pingSPin;
int firePin = A4;
Servo servoLeft;
Servo servoRight;
int fireState;
int fLeft= 180;
int fRight= 0;
int threshold = 700;              // distance threshold for sensors to tell how to navigate
int valLeft = 0;                  // variable to store the values from LEFT sensor(initially zero)
int valRight = 0;                 // variable to store the values from RIGHT sensor(initially zero)
int valForward = 0;               // variable to store the values from FORWARD sensor(initially zero)
int onLine = 0;
//right distance has min 132 max 768 pin A0
//front distance mins 132 andmax 767 pin A1
//left distance min 112 and max 767 pin A2
//line sensor min 16 and max is 1023 pin a 3
//fire has max of 985 pin a4 and a5


// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(fanPin, OUTPUT);
 
  //setup movement servos
  servoLeft.attach(6);
  servoRight.attach(3);
  servoLeft.write(90);
  servoRight.write(90);
}


// the loop routine runs over and over again forever:
void loop() 
{
  // check for fire sensor active:
  readSensors();// possibly want a read sensor method that takes a reading of all sensors readSensor()
  leftHandWallFollow();
  delay(1);        // delay in between reads for stability
  
  if(bottomLineSPin>50 && fireState){
    //stop moving
      
    //aim
    digitalWrite(fanPin, 145);
    
  }
  
  else if(!fireState)
  {
    leftHandWallFollow();
  }
    
}

void stopMoving()
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
    servoLeft.write(fRight);
    servoRight.write(fLeft);
  }
  void turnLeft()
  {
    servoLeft.write(90);
    servoRight.write(fRight);
  }
  void turnRight()
  {
    servoLeft.write(fLeft);
    servoRight.write(90);
  }
  void turnAround()
  {
    servoLeft.write(fLeft);
    servoRight.write(fLeft);
  }
  void readSensors()
  {
    valLeft = analogRead(leftDistancePin);
    valRight = analogRead(rightDistancePin);
    valForward = analogRead(frontDistancePin);
    fireState = analogRead(firePin);
    Serial.println("vleft " + valLeft);
    Serial.println("vright " + valRight);
    Serial.println("vforward " +  valForward);
    Serial.println("fs " + fireState);
    
  }
  void aim()
  {
    
    
  }
  
  void averageSensor()
  {

  }
  void leftHandWallFollow()
  {
    readSensors();
    
    if(valLeft > threshold && valRight > threshold && valForward < threshold) //2 way intersection
    {
      turnLeft();
    }
    
    else if(valLeft < threshold && valRight < threshold && (valForward > threshold) ) // empty space
    { 
        forward();//Moves straight                                                                                      
    }
    
    else if(valLeft < threshold && valRight < threshold && valForward < threshold)
    {
      backward();
      turnAround();
    }
    
    else if(valLeft > threshold) 
    {
      turnLeft(); // ???need to add amount of time to turn for???
    }
    
    else if(valLeft < threshold && valForward <threshold && valRight > threshold)
    {
      turnRight();
    }
    
  }
  
  
  




