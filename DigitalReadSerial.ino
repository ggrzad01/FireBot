#include<Servo.h>

int rightWallPin=A0;
int frontWallPin=A2;
int leftWallPin=A1;
int linePin=A3;
int leftFirePin=A4;
int rightFirePin=A5;

int leftWheelPin=6;
int rightWheelPin=3;
int fanPin=2;

Servo leftWheel;
Servo rightWheel;

int leftForward=180;
int rightForward=0;
int stopped=90;
int leftBack=rightForward;
int rightBack=leftForward;

int n=15;
int wallThreshold=600;
int wallMin=100;

int moveTime=0;
int turnTime=925;


int rightWallRead=0;
int leftWallRead=0;
int frontWallRead=0;
int lineRead=0;
int leftFireRead=0;
int rightFireRead=0;


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

  Serial.print("rightWallRead"); Serial.println(rightWallRead);
  Serial.print("frontWallRead"); Serial.println(frontWallRead);
  Serial.print("leftWallRead"); Serial.println(leftWallRead);

  leftWallFollow();

  reset();    
}

void sensorRead(){
    for(int x=0;x<=n;x++){
      rightWallRead+=analogRead(rightWallPin);
      frontWallRead+=analogRead(frontWallPin);
      leftWallRead+=analogRead(leftWallPin);
      lineRead+=analogRead(linePin);
      leftFireRead+=analogRead(leftFirePin);
      rightFireRead+=analogRead(rightFirePin);
    }
  //average Sensor reads
  rightWallRead/=n;
  frontWallRead/=n;
  leftWallRead/=n;
  lineRead/=n;
  leftFireRead/=n;
  rightFireRead/=n;}

void forward(){
  leftWheel.write(leftForward);
  rightWheel.write(rightForward);
  }

void backward(){
  leftWheel.write(leftBack);
  rightWheel.write(rightBack);
  }

void stopMoving(){
  leftWheel.write(stopped);
  rightWheel.write(stopped);
  }

void turnLeft(){
  leftWheel.write(stopped);
  rightWheel.write(rightForward);
  }

void turnRight(){
  leftWheel.write(leftForward);
  rightWheel.write(stopped);
  }

void cornerRight(){
  leftWheel.write(leftForward);
  rightWheel.write(rightBack);
  }

void cornerLeft(){
  leftWheel.write(leftBack);
  rightWheel.write(rightForward);
  }

void reset(){
  rightWallRead=0;
  frontWallRead=0;
  leftWallRead=0;
  lineRead=0;
  leftFireRead=0;
  rightFireRead=0;
}

void leftWallFollow(){
  //turn left in empty space
   if(frontWallRead > wallThreshold){
    if(leftWallRead>wallThreshold){
      cornerRight();
      delay(turnTime);}
    else if(rightWallRead>wallThreshold){
      cornerLeft();
      delay(turnTime);
      }
    else{}
  }

  
  
  else if(leftWallRead < wallThreshold ){
      //for(int x = 0 ;x += 50
      turnLeft();
      delay(moveTime);
      //forward();
      //delay(100); 
    }
    else if(rightWallRead < wallThreshold){
      turnRight();
      delay(moveTime);
    }
    
  else 
{
    forward();
    delay(moveTime);
    }
    }
  //right


  
