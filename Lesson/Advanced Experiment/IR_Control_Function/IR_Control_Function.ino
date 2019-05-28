#include "IR_remote.h"

#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  --- left 
#define IN4_PIN 9   // PWMA
#define IN3_PIN 5   // DIRA  --- right

int RECV_PIN = 11;//Define the infrared receiver pin to 11

byte expedite1 = 0x16;
byte expedite2 = 0x0D;
byte up = 0x18;
byte down = 0x52;
byte stop = 0x1c;
byte left = 0x08;
byte right = 0x5A;
static int val = 160;
IRremote irrecv(RECV_PIN);


void setup() {
  Serial.begin(9600);
  irrecv.begin();
}

void loop() {
  byte irKeyCode;
  if (irKeyCode = irrecv.getCode())
  {   
  
    if (irKeyCode == up) 
    {
       Serial.println(irKeyCode,HEX);
      analogWrite(IN1_PIN, 0);//the speed value of motorA is val
      analogWrite(IN2_PIN, val);
      analogWrite(IN3_PIN, val);
      analogWrite(IN4_PIN, 0); //the speed value of motorA is val
    }
    else if (irKeyCode == expedite1) {
      val += 20;
      if (val >= 240)
      {
        val = 255;
      }
    }
    else if (irKeyCode == expedite2) {
      val -= 20;
      if (val <= 20)
      {
        val = 0;
      }
    }
    else if (irKeyCode == stop) {
      analogWrite(IN1_PIN, 0);
      analogWrite(IN2_PIN, 0);
      analogWrite(IN3_PIN, 0);
      analogWrite(IN4_PIN, 0);
    }
    else if (irKeyCode == left) {
      analogWrite(IN1_PIN, val);
      analogWrite(IN2_PIN, 0); //the speed value of motorA is val
      analogWrite(IN3_PIN, val);
      analogWrite(IN4_PIN, 0); //the speed value of motorA is val
    }
    else if (irKeyCode == right) {
      analogWrite(IN1_PIN, 0);//the speed value of motorA is val
      analogWrite(IN2_PIN, val);
      analogWrite(IN3_PIN, 0);//the speed value of motorA is val
      analogWrite(IN4_PIN, val);
    }
    else if (irKeyCode == down) {
      analogWrite(IN1_PIN, val);
      analogWrite(IN2_PIN, 0); //the speed value of motorA is val
      analogWrite(IN3_PIN, 0); //the speed value of motorA is val
      analogWrite(IN4_PIN, val);
    }
  } else {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 0); //the speed value of motorA is 0
    analogWrite(IN3_PIN, 0);
    analogWrite(IN4_PIN, 0); //the speed value of motorB is 0
  }
}
