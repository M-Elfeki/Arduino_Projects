#include <Servo.h>
Servo servoFrontRight;
Servo servoFrontLeft;
Servo servoBack;
int pos=0;

void setup()
{
  Serial.begin(9600);
  servoFrontRight.attach(9);
  servoFrontLeft.attach(8);
  servoBack.attach(10);
  servoFrontRight.write(179);
  servoFrontLeft.write(0);
  servoBack.write(90);
  forward();
}

void loop()
{
  if(getDistance(7)<20&&getDistance(12)<20)
  {
    int r=exploreRight();
    int l=exploreLeft();
    if(r==1)
    {
      right45();
      forward();
    }
    else if(l==1)
    {
      left45();
      forward();
    }
    else if(r==2)
    {
      right90();
      forward();
    }
    else if(l==2)
    {
      left90();
      forward();
    }
    else if(exploreBack())
    {
      backward();
      delay(3000);
      right90();
      forward();
    }
    else off();
  }
  else if(getDistance(7)<20&&getDistance(12)>=20)
  {
    int r=exploreRight();
    int l=exploreLeft();
    if(r==1)
    {
      right45();
      forward();
      delay(2000);
      left45();
      forward();
    }
    else if(r==2)
    {
      right90();
      forward();
      delay(2000);
      left90();
      forward();
    }
    else if(l==1)
    {
      left45();
      forward();
      delay(2000);
      right45();
      forward();
    }
    else if(l==2)
    {
      left90();
      forward();
      delay(2000);
      right90();
      forward();
    }
    else if(exploreBack())
    {
      backward();
      delay(3000);
      right90();
      forward();
    }
    else off();
  }
  else if(getDistance(7)>=20&&getDistance(12)<20)
  {
    int r=exploreRight();
    int l=exploreLeft();
    if(l==1)
    {
      left45();
      forward();
      delay(2000);
      right45();
      forward();
    }
    else if(l==2)
    {
      left90();
      forward();
      delay(2000);
      right90();
      forward();
    }
    else if(r==1)
    {
      right45();
      forward();
      delay(2000);
      left45();
      forward();
    }
    else if(r==2)
    {
      right90();
      forward();
      delay(2000);
      left90();
      forward();
    }
    else if(exploreBack())
    {
      backward();
      delay(3000);
      right90();
      forward();
    }
    else off();
  }
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
  return cm;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

int exploreRight()
{
  for(pos=177;pos>=135;pos-=3)
  {
    servoFrontRight.write(pos);
    delay(10);
  }
  if(getDistance(12)>20)
  {
    servoFrontRight.write(179);
    return 1; 
  }
  for(pos=135;pos>=90;pos-=3)
  {
    servoFrontRight.write(pos);
    delay(10);
  }
  if(getDistance(12)>20)
  {
    servoFrontRight.write(179);
    return 2;
  }
  else
  {
    servoFrontRight.write(179);
    return 0;
  }
}

int exploreLeft()
{
  for(pos=0;pos<=45;pos+=3)
  {
    servoFrontLeft.write(pos);
    delay(10);
  }
  if(getDistance(7)>20)
  {
    servoFrontLeft.write(0);
    return 1;
  }
  for(pos=45;pos<90;pos+=3)
  {
    servoFrontLeft.write(pos);
    delay(10);
  }
  if(getDistance(7)>20)
  {
    servoFrontLeft.write(0);
    return 2;
  }
  else
  {	
    servoFrontLeft.write(0);
    return 0;
  }
}

bool exploreBack()
{
  servoBack.write(179);
  delay(200);
  servoFrontLeft.write(179);
  int d=getDistance(7);
  delay(200);
  servoBack.write(90);
  delay(200);
  servoFrontLeft.write(0);
  return d>30;
}
