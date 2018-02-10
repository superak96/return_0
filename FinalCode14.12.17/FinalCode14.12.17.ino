#include <Time.h>
#include <TimeLib.h>
#include<Servo.h>

//fixtures for hand and claw setup
int sLeftPin=4;
int sR8Pin=3;
int clawPin=6;
Servo sLeft;
Servo sR8;
Servo claw;

//codeword to transfer message
char val;




//fixtures of L293-D
int leftFwd = 10;
int leftBwd = 11;
int rightFwd = 12;
int rightBwd = 13;


void setup()
    {
        Serial.begin(9600);
        
        //setup for L293D
        pinMode(leftFwd, OUTPUT);
        pinMode(leftBwd, OUTPUT);
        pinMode(rightFwd, OUTPUT);
        pinMode(rightBwd, OUTPUT);

        //setup hand servo setup
        sLeft.attach(sLeftPin);
        sR8.attach(sR8Pin);
        claw.attach(clawPin);
    }


void grab()
    {
         claw.write(180);
    }
void drop()
    {
        claw.write(0);
    }

void loop()
{
  while (Serial.available() > 0)
  {
  val = Serial.read();
  Serial.println(val);
  }

  if( val == 'F') // move Forward
    {
      digitalWrite(leftFwd, HIGH);
      digitalWrite(leftBwd, LOW);
      digitalWrite(rightFwd, HIGH);
      digitalWrite(rightBwd, LOW); 
    }
  else if(val == 'B') //move  Backward
    {
      digitalWrite(leftFwd, LOW);
      digitalWrite(leftBwd, HIGH);
      digitalWrite(rightFwd, LOW);
      digitalWrite(rightBwd, HIGH); 
    }
  
    else if(val == 'L') //move Left
    {
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, HIGH);
    digitalWrite(rightBwd, LOW);
    }
    else if(val == 'R') //move Right
    {
    digitalWrite(leftFwd, HIGH);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, LOW); 
    }
    
  else if(val == 'S') //Stop
    {
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, LOW); 
    }
  else if(val == 'I') //move Forward Right
    {
    digitalWrite(leftFwd, HIGH);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, LOW);
    }
  else if(val == 'J') //move Backward Right
    {
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, HIGH);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, LOW);
    }
   else if(val == 'G') //move Forward Left
    {
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, HIGH);
    digitalWrite(rightBwd, LOW);
    }
  else if(val == 'H') //move Backward Left
    {
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, HIGH); 
    }

    else if(val == 'V')  // to grab using claw 
    {
      grab();
    }
    
    else if(val == 'v') //to drop 
    {
      drop();
    }

   else if(val == '0') //hand is up on 0
    {
     sLeft.write(120);
     sR8.write(40);
    }
    
    else if(val == '1') 
    {
      sLeft.write(110);
        sR8.write(50);
    }
    else if(val == '3') 
    {
      sLeft.write(100);
        sR8.write(60);
    }
    else if(val == '4') 
    {
      sLeft.write(90);
        sR8.write(70);
    }
    else if(val == '5')
    {
      sLeft.write(80);
        sR8.write(80);
    }
    else if(val == '6')
    {
      sLeft.write(70);
        sR8.write(90);
    }
    else if(val == '7')
    {
      sLeft.write(60);
        sR8.write(100);
    }

     else if(val == '8')
    {
      sLeft.write(50);
        sR8.write(110);
    }
    else if(val == '9') //hands down!!
    {
      sLeft.write(35);
        sR8.write(125);
    }

    
}

