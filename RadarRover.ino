#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 9, 10, 11, 12);
Servo s;

int servo = 13;

int echo = 7;
int trig = 8;

int buzzer = 3;

int maxDistance = 12;

double distance;
long duration;
bool detected;

void setup() 
{
  lcd.begin(16, 2);
  lcd.print("STATUS: ");
  lcd.setCursor(0,1);
  lcd.print("Distance:     in");

  s.attach(servo);
  //s.write(90);
  //delay(500);

  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);
}


void measure()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration*0.0343)/2; //x = vt, v = 0.0343, speed of sound in cm/microsec
  distance = distance/2.54;

  if(distance > 0 && distance < maxDistance)
  {
    detected = true;
  }
  else
  {
    detected = false;
  }

  if(detected)
  {
    if(distance<4)
    {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
    }
    else if(distance >=4 && distance <= 8)
    {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500);
    }
    else if(distance > 8 && distance < maxDistance)
    {
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }

    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    lcd.setCursor(8,0);
    lcd.print("FOUND   ");
    lcd.setCursor(9,1);
    lcd.print(distance);
  }
  else
  {
    lcd.setCursor(8,0);
    lcd.print("MISSING");
    lcd.setCursor(9,1);
    lcd.print("     ");
  }

}
void loop()
{
  for(int i = 0; i <=180; i+=3)
  {
    while(detected)
    {
      measure();
      delay(50);
    }
    s.write(i);
    delay(50);
    measure();
  }
  for(int i = 180; i>= 0; i-=3)
  {
    while(detected)
    {
      measure();
      delay(50);
    }
    s.write(i);
    delay(50);
    measure();
  }
}
