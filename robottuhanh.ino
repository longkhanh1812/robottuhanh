#include<Servo.h>

#define IN1_L298_PIN 2
#define IN2_L298_PIN 4
#define IN3_L298_PIN 7
#define IN4_L298_PIN 8
#define ENA_PIN 5
#define ENB_PIN 6                                                                  
#define echo_PIN 11
#define trig_PIN 12
#define servo_PIN 3

Servo servosg;

void motor_stop()
{
  digitalWrite(IN1_L298_PIN,LOW);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,LOW);
  digitalWrite(IN4_L298_PIN,LOW);
  
}
void motor_up()
{
  analogWrite(ENA_PIN,80);
  analogWrite(ENB_PIN,60);
  digitalWrite(IN1_L298_PIN,HIGH);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,HIGH);
  digitalWrite(IN4_L298_PIN,LOW);
  
}
void motor_back()
{
  analogWrite(ENA_PIN,120);
  analogWrite(ENB_PIN,120);
   digitalWrite(IN1_L298_PIN,LOW);
  digitalWrite(IN2_L298_PIN,HIGH);
  digitalWrite(IN3_L298_PIN,LOW);
  digitalWrite(IN4_L298_PIN,HIGH);
  
}
void motor_left()
{
  analogWrite(ENA_PIN,100);
  analogWrite(ENB_PIN,0);
   digitalWrite(IN1_L298_PIN,HIGH);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,LOW);
  digitalWrite(IN4_L298_PIN,LOW);
  
}
void motor_right()
{
   analogWrite(ENA_PIN,0);
  analogWrite(ENB_PIN,100);
   digitalWrite(IN1_L298_PIN,LOW);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,HIGH);
  digitalWrite(IN4_L298_PIN,LOW);
 
}
int getDistance()
{
  int duration, distanceCm;
  digitalWrite(trig_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_PIN, LOW);
  duration = pulseIn(echo_PIN, HIGH);
  distanceCm = (int)duration / 29.1 / 2;
  return distanceCm;
}


void setup()
{
  Serial.begin(9600);
  servosg.attach(servo_PIN);
  servosg.write(90);
  pinMode(trig_PIN,OUTPUT);
  pinMode(echo_PIN,INPUT);
  pinMode(IN1_L298_PIN,OUTPUT);
  pinMode(IN2_L298_PIN,OUTPUT);
  pinMode(IN3_L298_PIN,OUTPUT);
  pinMode(IN4_L298_PIN,OUTPUT);
  pinMode(ENA_PIN,OUTPUT);
  pinMode(ENB_PIN,OUTPUT);
  
  
}


void loop()
{
  int distance;
  int distance0,distance180;
  distance=getDistance();
 
  if(distance <=15)
  {
    motor_stop();
    delay(100);
    motor_back();
    delay(300);
    motor_stop();
    delay(200);
    servosg.write(0);
    distance0=getDistance();
    delay(100);
    servosg.write(35);
    delay(100);
    servosg.write(70);
    delay(100);
    servosg.write(105);
    delay(100);
    servosg.write(145);
    delay(100);
    servosg.write(180);
    distance180=getDistance();
    delay(100);
    servosg.write(90);
   
    if((distance0 < 15)&& (distance180 < 15))
    {
      motor_back();
      delay(300);
      motor_stop();
      delay(300);
    }
    else
    if( distance0 >distance180)
    {
      motor_right();
      delay(300);
    }
    else
    if( distance0 <=distance180)
    {
      motor_right();
      delay(300);
    }
    
    
    
  }
  else
  {
   
    motor_up();
  }
      
  
  
  
}
