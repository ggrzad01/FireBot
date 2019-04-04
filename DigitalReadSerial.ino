#include<Servo.h>

int rightWallPin = A0;
int frontWallPin = A2;
int leftWallPin = A1;
int linePin = A3;
int leftFirePin = A4;
int rightFirePin = A5;

int leftWheelPin = 6;
int rightWheelPin = 3;
int fanPin = 2;

Servo leftWheel;
Servo rightWheel;

int leftForward = 180;
int rightForward = 0;
int stopped = 90;
int leftBack = rightForward;
int rightBack = leftForward;

int n = 15;
int innerThreshold = 300;
int frontThreshold = 400;
int outerThreshold = 500;
int wallMin = 100;

int moveTime = 25;
int turnTime = 925;


int rightWallRead = 0;
int leftWallRead = 0;
int frontWallRead = 0;
int lineRead = 0;
int leftFireRead = 0;
int rightFireRead = 0;

int maximum = 0;
int minimum = 1024;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  leftWheel.attach(leftWheelPin);
  rightWheel.attach(rightWheelPin);
  leftWheel.write(stopped);
  rightWheel.write(stopped);
}

void loop() {
  //get Sensor reads
  sensorRead();
  //  int rightWallPin = A0;
  //  int frontWallPin = A2;
  //  int leftWallPin = A1;
  minimum = min(analogRead(A0), minimum); // if(Sensor < minimum){minimum = Sensor; } //
  maximum = max(analogRead(A0), maximum);


  Serial.print(" rightWallRead: ");
  Serial.print(rightWallRead);
  Serial.print("\tfrontWallRead: ");
  Serial.print(frontWallRead);
  Serial.print("\tleftWallFollow: ");
  Serial.print(leftWallRead);
  Serial.print(" \tminimum: ");
  Serial.print(minimum);
  Serial.print("\tmaximum: ");
  Serial.print(maximum);
  Serial.println(" ");

  leftWallFollow();
    
}

void sensorRead() {
  for (int x = 0; x <= n; x++) 
  {
    rightWallRead += analogRead(rightWallPin);
    frontWallRead += analogRead(frontWallPin);
    leftWallRead += analogRead(leftWallPin);
    lineRead += analogRead(linePin);
    leftFireRead += analogRead(leftFirePin);
    rightFireRead += analogRead(rightFirePin);
  }
  
  //average Sensor reads
  
  rightWallRead /= n;
  frontWallRead /= n;
  leftWallRead /= n;
  lineRead /= n;
  leftFireRead /= n;
  rightFireRead /= n;
}

void forward() 
{
  leftWheel.write(leftForward);
  rightWheel.write(rightForward);
}

void backward() 
{
  leftWheel.write(leftBack);
  rightWheel.write(rightBack);
}

void stopMoving() 
{
  leftWheel.write(stopped);
  rightWheel.write(stopped);
}

void turnLeft() 
{
  leftWheel.write(stopped);
  rightWheel.write(rightForward);
}

void turnRight() 
{
  leftWheel.write(leftForward);
  rightWheel.write(stopped);
}

void cornerRight()
{
  leftWheel.write(leftForward);
  rightWheel.write(rightBack);
}

void cornerLeft()
{
  leftWheel.write(leftBack);
  rightWheel.write(rightForward);
}

void reset()
{
  rightWallRead = 0;
  frontWallRead = 0;
  leftWallRead = 0;
  lineRead = 0;
  leftFireRead = 0;
  rightFireRead = 0;
}

void blowFan()
{
 
}

void leftWallFollow() 
{

  int fireTurnTime = abs(rightFireRead-leftFireRead);
  int fireThreshold = 450;
  
  if(leftFireRead == rightFireRead && leftFireRead > fireThreshold) //checks
  {
    blowFan();
    delay(1000); 
  }
  
  else 
  {
    if(leftFireRead > rightFireRead) 
   {
      turnLeft();
      delay(fireTurnTime); 
    } 
    if(leftFireRead < rightFireRead) 
    {
      turnRight();
      delay(fireTurnTime); 
    }
  
    if (frontWallRead > frontThreshold) //if there is something in front turn left
    { 
      cornerLeft();
      delay(turnTime);
    }
    else 
    {
      if (rightWallRead > 500)          //if the right wall gets too close turn left
      {
        turnLeft();
        delay(moveTime);
      }
      else if (rightWallRead < 300)     //if the right gets too far away turn right
      {
        turnRight();
        delay(moveTime);
      }
      else                              //otherwise go forward
      {
        forward();
        delay(moveTime);
      }
    }
  }
}

