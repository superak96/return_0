//draft 0- by ajeet
//trying out time stuff so dat beast comes back at same postion aftr pickin up!

//libraries call
#include <Time.h>
#include <TimeLib.h>
#include<Servo.h>
#define handClearance 25.00   //in cm
#define batteryCorrection 100 //in microcseconds
#define range 100    //in cm

//pins of hand servo setup
int sFingersPin=6;
int sElbowPin=8;

//pins of L293-D
int leftFwd = 11;
int leftBwd = 10;
int rightFwd = 13;
int rightBwd = 12;

//pins for SRO4(sonar)
int echo = 8;
int trig = 7;
float cm;

//creating 3 servo objects of servo class
Servo sFinger1;
Servo sFinger2;
Servo sElbow;

//global declearations
time_t t_forScan1,t_forScan2;
int i;

void setup()
    {
        Serial.begin(9600);
        
        //fixtures for L293D
        pinMode(leftFwd, OUTPUT);
        pinMode(leftBwd, OUTPUT);
        pinMode(rightFwd, OUTPUT);
        pinMode(rightBwd, OUTPUT);

        //fixtures for SRO4
        pinMode(trig,OUTPUT);
        pinMode(echo,INPUT);

        //fixtures hand servo setup
        sFinger1.attach(sFingersPin);
        sFinger2.attach(sFingersPin);          
        sElbow.attach(sElbowPin);
    }

//function to get object dis
float objDis()
{
    float dist;
    digitalWrite(trig,HIGH);
    delayMicroseconds(500);
    digitalWrite(trig,LOW);
    dist = (pulseIn(echo,HIGH)/2)/29.1;
    return dist;
    
}

//functions for L293 movement
void Fwd()
{
    digitalWrite(leftFwd, HIGH);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, HIGH);
    digitalWrite(rightBwd, LOW);
}
void Bwd()
{
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, HIGH);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, HIGH);
}

void r8()
{
    digitalWrite(leftFwd, HIGH);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, LOW);
}

void left()
{
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, HIGH);
    digitalWrite(rightBwd, LOW);
}


void leftBack()
{
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, HIGH);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, LOW);
}

void uTurn()
{
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, HIGH);
    digitalWrite(rightBwd, LOW);
}

void deadStop()
{
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftBwd, LOW);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightBwd, LOW);
}

//funtion to get the time diff
float timeDiff(time_t t1,time_t t2)
{
    float time1,time2,timeDiff;
    time1 = second(t1);
    time2 = second(t2);
    timeDiff = (time2-time1)*1000;
    return timeDiff;
    
}

//function to go fwd towrds object, stop for pickup and back to pos 1
void pos_1_2_1()
{
            
    time_t t1,t2;
    t1=now();
    while( objDis() >= handClearance)
      Fwd();
 

    deadStop();
    //reached near objct, now taking time2
    t2=now();
    
    //delay for pickup   
    delay(2000);
    
    Bwd();
    delay(timeDiff(t1,t2));
    
    deadStop();
}


//fn for hand working
void elbowDown()
    {
        for(i=70;i>=10;i=i-15)
        {
          delay(500);
          sElbow.write(i); 
        }
                 
    }
void elbowUp()
    {
        sElbow.write(70);
    }

void grab()
    {
         sFinger1.write(90);
         sFinger2.write(90);;  
    }
void drop()
    {
        sFinger1.write(0);
        sFinger2.write(0);  
    }

//fn for posn 0 to 1 i.e. scaning the object n deadstop as soon as it finds  a object
void scan()
{
     //take the dustbin by default on left

     //clockin before d start
     t_forScan1=now();
     Serial.println(t_forScan1);

     //now jst keep scaning until n unless object found
     while(objDis()>range)
        left();
     deadStop();
     t_forScan2=now();
     Serial.println(t_forScan2);
      
}

  
void loop() 
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2000);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  //duration=pulseIn(echo,HIGH);
  //Serial.println(duration);
  cm=(pulseIn(echo,HIGH)/2)/29.1;
  Serial.println(cm);
  delay(500);
}
