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

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  --- left 
#define INPUT3_PIN 5   // PWMA
#define INPUT4_PIN 9   // DIRA  --- right 
const int TrigPin = 2; 
const int EchoPin = 3; 
int ServoPin = 13;    
float da;   
float dl;    
float dr;    

void SetServoDegree(int Angle)
{
  Serial.println(Angle);  //Output data to the serial port for observation
  for (int i = 0; i < 80; i++) {
    float pulsewidth = (Angle * 11) + 350;
    digitalWrite(ServoPin, HIGH);   //Set the servo interface level to high
    delayMicroseconds(pulsewidth);  //The number of microseconds of the delay pulse width value
    digitalWrite(ServoPin, LOW);    //Set the servo interface level to low
    delayMicroseconds(20000 - pulsewidth);
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(ServoPin, OUTPUT);
  pinMode(INPUT1_PIN, OUTPUT); 
  pinMode(INPUT2_PIN, OUTPUT);
  pinMode(INPUT3_PIN, OUTPUT);
  pinMode(INPUT4_PIN, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  SetServoDegree(90); 
  delay(1000);
}

void loop()
{
  analogWrite(TrigPin, 0); 
  delayMicroseconds(2);
  analogWrite(TrigPin, 255);
  delayMicroseconds(10);
  analogWrite(TrigPin, 0);
  da = pulseIn(EchoPin, HIGH) / 58.0; 
  if (da >= 10 )
  {  
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 120);
    analogWrite(INPUT3_PIN, 120);
    analogWrite(INPUT4_PIN, 0);
    
  }
  else if ((da >= 15) && (da <= 25) )

  {
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 0 );
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 0);
  }
  else if (da < 15) 
  {
    analogWrite(INPUT1_PIN, 120);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 120);  
  }
}
