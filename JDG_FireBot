#include<Servo.h>

int rightWallPin = A0;
int frontWallPin = A2;
int leftWallPin = A1;
int linePin = A3;
int leftFirePin = A5;
int rightFirePin = A4;
int fireThreshold = 200;
int leftWheelPin = 6;
int rightWheelPin = 3;
int fanPin1 = 12;
int fanPin2 = 13;
int fanPinPwm = 9;
int chooseWallPin = 0;
int countTick=0;

Servo leftWheel;
Servo rightWheel;

int leftForward = 180;
int rightForward = 0;
int stopped = 90;
int leftBack = rightForward;
int rightBack = leftForward;

int n = 15;
int innerThreshold = 320;
int frontThreshold = 400;
int outerThreshold = 500;
int wallMin = 100;

int moveTime = 0;
long leftFollowTimer=300;

bool chooseWallBool=false;

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
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  pinMode(fanPinPwm, OUTPUT);
  leftWheel.attach(leftWheelPin);
  rightWheel.attach(rightWheelPin);
  leftWheel.write(stopped);
  rightWheel.write(stopped);
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
  digitalWrite(fanPin1, HIGH);
  digitalWrite(fanPin2, LOW);
  digitalWrite(fanPinPwm, HIGH);
  delay(1000);
  digitalWrite(fanPin1, LOW);
}
void rightWallFollow()
{
  
  
  if (frontWallRead > frontThreshold) //if there is something in front turn left
  {
    cornerLeft();
    delay(moveTime);
  }

  
  else
  {
    if (rightWallRead > outerThreshold)          //if the right wall gets too close turn left
    {
      turnLeft();
      delay(moveTime);
    }
    else if (rightWallRead < innerThreshold)     //if the right gets too far away turn right
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
  void leftWallFollow()
  {
    
    if (frontWallRead > frontThreshold) //if there is something in front turn left
    {
      cornerRight();
      delay(moveTime);
    }
    
    else
    {
      if (leftWallRead > outerThreshold)          //if the right wall gets too close turn left
      {
        turnRight();
        delay(moveTime);
      }
      else if (leftWallRead < innerThreshold)     //if the right gets too far away turn right
      {
        turnLeft();
        delay(moveTime);
      }

      else                              //otherwise go forward
      {
        forward();
        delay(moveTime);
      }
    }
  }
  void maze()
  {
    int fireTurnTime = abs((rightFireRead-leftFireRead)*2);
    if (rightFireRead > fireThreshold && leftFireRead > fireThreshold) //checks
    {
      //Serial.println("blowFan");
      blowFan();
      delay(10);
    }

    else
    {

      if (leftFireRead - rightFireRead > 200)
      {
        turnLeft();
        delay(fireTurnTime);
      }
      if (rightFireRead - leftFireRead > 200 )
      {
        turnRight();
        delay(fireTurnTime);
      }
      //choose left or right wall follow
      else
      {
        if(chooseWallPin!=0)
        {
          rightWallFollow();
        }
        else{
           if(chooseWallBool==false){forward();delay(10000);chooseWallBool=true;}
        
           leftWallFollow();}
        }
        
        
       //long randNumber;
        //randNumber = random(100);
        /**if (randNumber <= 89 || !changeRoute)
        {
          rightWallFollow();
          changeRoute
        }*/
/**
        if(countTick<=1100){
            rightWallFollow();
            countTick++;
          }
        else if(countTick>1100&&countTick<=1500){
            leftWallFollow();
            countTick++;
          }
        else{countTick=0;}
   */     
        /**else
        {
          leftWallFollow();
          changeRoute = true;
        }*/
      }
  }



  void loop() {
    //get Sensor reads
    sensorRead();
    //  int rightWallPin = A0;
    //  int frontWallPin = A2;
    //  int leftWallPin = A1;
    //minimum = min(analogRead(A0), minimum); // if(Sensor < minimum){minimum = Sensor; } //
    //maximum = max(analogRead(A0), maximum);

    /**
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
    Serial.print( "\tRightFireSensor");
    Serial.print(rightFireRead);
    Serial.print( "\tLeftFireSensor");
    Serial.print(leftFireRead);
    Serial.println(" ");
    **/

    maze();
  }
