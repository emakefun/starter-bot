#include "RgbUltrasonic.h"
#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  --- left 
#define IN3_PIN 5   // PWMA
#define IN4_PIN 9   // DIRA  --- right 
int ServoPin = 13;    
#define SING_PIN 3
#define RGB_PIN 2
#define SERVO_PIN 13
#define UL_LIMIT_MID 15
#define UL_LIMIT_MAX 20
RgbUltrasonic mRgbUltrasonic(SING_PIN, RGB_PIN, SERVO_PIN);/*Define ultrasonic and servo pins*/
float FrontDistance;
void setup()
{
  Serial.begin(9600);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  mRgbUltrasonic.SetServoBaseDegree(90);/*Adjust the initial angle of the steering gear according to the steering gear error*/
  mRgbUltrasonic.SetServoDegree(90);/*Set the servo angle*/
}

void loop()
{
 FrontDistance = mRgbUltrasonic.GetUltrasonicFrontDistance();/*The ultrasonic module collects the front data*/
  delay(50);
  if ((FrontDistance > UL_LIMIT_MID) && (FrontDistance < UL_LIMIT_MAX))
  {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 0);
    analogWrite(IN3_PIN, 0);
    analogWrite(IN4_PIN, 0);
  } 
 if (FrontDistance < UL_LIMIT_MID)
  {
    analogWrite(IN1_PIN, 150);
    analogWrite(IN2_PIN, 0);
    analogWrite(IN3_PIN, 0);
    analogWrite(IN4_PIN, 150);     
    }
    if (FrontDistance > UL_LIMIT_MAX)
    {
      analogWrite(IN1_PIN, 0);
      analogWrite(IN2_PIN, 150);
      analogWrite(IN3_PIN, 150);
      analogWrite(IN4_PIN, 0);
    }
}
