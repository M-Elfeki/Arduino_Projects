#include <Servo.h>
#define IRleft 1 
#define IRright 2
#define IRup 3 
#define IRdown 0 
#define IRleds 13
#define panPin 10 

byte LRscalefactor=10;
const int distancemax=2, bestdistance=450, PanZero=0
          , LRmax=170, LRmin=10;
int pan=PanZero, panscale, distance, leftright, leftIRvalue
    , rightIRvalue, downIRvalue, upIRvalue;
Servo panLR;
Servo front;

void setup()
{
  Serial.begin(9600);
  panLR.attach(panPin);
  panLR.write(PanZero);
  front.attach(8);
  front.write(100);
  pinMode (IRleds,OUTPUT);
}

void loop()
{
  parkOne();
}

void parkOne()
{
  while(IRfollow()<25)
  {
    right();
  }
  off();
}
void right()
{
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);    
}

void backward()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

bool isBackward()
{
  return (digitalRead(2)==HIGH&&digitalRead(3)==LOW&&
          digitalRead(4)==LOW&&digitalRead(5)==HIGH);
}

void forward()
{
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);  
}

bool isForward()
{
  return (digitalRead(2)==LOW&&digitalRead(3)==HIGH&&
          digitalRead(4)==HIGH&&digitalRead(5)==LOW);
}

void left90()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW); 
  delay(1380);
}

void left45()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW); 
  delay(690);
}



void right90()
{
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);    
  delay(1380);  
}

void right45()
{
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);    
  delay(690);  
}



void off()
{
  
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);     
}

bool isOff()
{
  return (digitalRead(2)==LOW&&digitalRead(3)==LOW&&
          digitalRead(4)==LOW&&digitalRead(5)==LOW);
}


int getDistance(int pingPin)
{
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  delay(15);
  return cm;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}


void IReye()
{
  digitalWrite(IRleds,HIGH);                                  
  delay(5);                                                   
  leftIRvalue=analogRead(IRleft);                             
  rightIRvalue=analogRead(IRright);                           
  upIRvalue=analogRead(IRup);                                
  downIRvalue=analogRead(IRdown);                            
  delay(2);
  digitalWrite(IRleds,LOW);                                   
  delay(5);                                                   
  leftIRvalue-=analogRead(IRleft);                 
  rightIRvalue-=analogRead(IRright);              
  upIRvalue-=analogRead(IRup);                       
  downIRvalue-=analogRead(IRdown);                  
  distance=(leftIRvalue+rightIRvalue+upIRvalue+downIRvalue)/4;
}

int IRfollow ()
{
  IReye();   
  if(distance<distancemax)
  {
    if(pan>PanZero)pan--;
    else pan++;
  }
  else
  {
    panscale=(leftIRvalue+rightIRvalue)*LRscalefactor/10;   
    if(leftIRvalue>rightIRvalue)
    {
      leftright=(leftIRvalue-rightIRvalue)*15/panscale;
      pan=pan-leftright;
    }
    else
    {
      leftright=(rightIRvalue-leftIRvalue)*15/panscale;
      pan=pan+leftright;
    }
    if (pan<LRmin) pan=LRmin;
    if (pan>LRmax) pan=LRmax;
  }
  panLR.write(pan);
  int d=getDistance(12);

  return d;
}
