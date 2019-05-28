/***********************************************************************
        __                                                          _
       / /        _____  __    __  _          _   (_)   ________   | |
      / /____   / _____) \ \  / / | |   __   | |  | |  (  ______)  | |_____
     / / ___/  | |_____   \ \/ /  | |  /  \  | |  | |  | |______   |  ___  |
    / /\ \     | |_____|   \  /   | | / /\ \ | |  | |  (_______ )  | |   | |
   / /  \ \__  | |_____    / /    | |/ /  \ \| |  | |   ______| |  | |   | |
  /_/    \___\  \______)  /_/      \__/    \__/   |_|  (________)  |_|   |_|


  KeyWay Tech firmware

  Copyright (C) 2015-2020

  This program is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation, in version 3.
  learn more you can see <http://www.gnu.org/licenses/>.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.

*/
#include "RgbUltrasonic.h"
#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  --- left 
#define IN3_PIN 5   // PWMA
#define IN4_PIN 9   // DIRA  --- right 
const int TrigPin = 2; 
const int EchoPin = 3; 
int ServoPin = 13;    
float da;   
float dl;    
float dr;    

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
  digitalWrite(SING_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SING_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SING_PIN, LOW);
  pinMode(SING_PIN, INPUT);
  FrontDistance = pulseIn(SING_PIN, HIGH) / 58.00;
  Serial.println(FrontDistance);
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
