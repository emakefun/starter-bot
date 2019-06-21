#include "StarterBot.h"
#include "BluetoothHandle.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  ---  left
#define IN3_PIN 5   // DIRA  ---  right
#define IN4_PIN 9   // PWMA

#define SERVO_PIN 13
#define UL_SING_PIN 3
#define UL_RGB_PIN 2
#define PHOTOSENSITIVE_LEFT_PIN A3
#define PHOTOSENSITIVE_RIGHT_PIN A4
#define IR_AVOIDANCE_LEFT_PIN 12
#define IR_AVOIDANCE_RIGHT_PIN A5

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);
byte Ps2xStatus, Ps2xType;

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_ULTRASONIC_FOLLOW_MODE);
  StarterBot.SetRgbUltrasonicPin(UL_SING_PIN, UL_RGB_PIN, SERVO_PIN);
  StarterBot.SetPhotoInfraredAvoidancePin(IR_AVOIDANCE_LEFT_PIN, IR_AVOIDANCE_RIGHT_PIN, PHOTOSENSITIVE_LEFT_PIN, PHOTOSENSITIVE_RIGHT_PIN);
  StarterBot.SetSpeed(0);
  StarterBot.mRgbUltrasonic->SetServoBaseDegree(90);
  StarterBot.mRgbUltrasonic->SetServoDegree(90);

}

void UltrasonicFollow()
{
  StarterBot.SetSpeed(50);
  uint16_t  LeftValue ,RightValue,UlFrontDistance;
  LeftValue = StarterBot.GetInfraredAvoidanceValue(0);
  RightValue = StarterBot.GetInfraredAvoidanceValue(1);
  UlFrontDistance =  StarterBot.GetUltrasonicValue(FRONT);
  delay(10);
  
  if ((UlFrontDistance <5)&&(RightValue != IA_THRESHOLD) && (LeftValue != IA_THRESHOLD))
  {
    StarterBot.GoBack();
  } 
   else if ((UlFrontDistance <5)&&(RightValue == IA_THRESHOLD) && (LeftValue != IA_THRESHOLD)) 
  {
     StarterBot.SetSpeed(70);
     StarterBot.Drive(40);
  } 
  else if ((UlFrontDistance <5)&&(RightValue != IA_THRESHOLD) && (LeftValue == IA_THRESHOLD)) 
  {
     StarterBot.SetSpeed(70);
     StarterBot.Drive(120);
  } 
  else if ((UlFrontDistance > 8)&&(RightValue != IA_THRESHOLD) && (LeftValue != IA_THRESHOLD)) 
  {
    StarterBot.GoForward();
  } 
  else if((UlFrontDistance > 8)&&(RightValue == IA_THRESHOLD) && (LeftValue != IA_THRESHOLD))
  {
     StarterBot.SetSpeed(70);
     StarterBot.Drive(15);
    }
    else if((UlFrontDistance > 8)&&(RightValue != IA_THRESHOLD) && (LeftValue == IA_THRESHOLD))
  {
     StarterBot.SetSpeed(70);
     StarterBot.Drive(165);
    }
     else if ((5 <= UlFrontDistance <=8)&&(RightValue = IA_THRESHOLD) && (LeftValue != IA_THRESHOLD)) 
  {
    StarterBot.SetSpeed(70);
     StarterBot.Drive(10);
    }
     else if ((5 <= UlFrontDistance <=8)&&(RightValue = IA_THRESHOLD) && (LeftValue != IA_THRESHOLD)) 
  {
    StarterBot.SetSpeed(70);
     StarterBot.Drive(170);
    }
  else if ((5 <= UlFrontDistance <=8)&&(RightValue != IA_THRESHOLD) && (LeftValue = IA_THRESHOLD)) 
  {
    StarterBot.KeepStop();
    }
}

void loop()
{
 
  switch (StarterBot.GetControlMode()) 
  {
    case E_ULTRASONIC_FOLLOW_MODE:
      UltrasonicFollow();
      break;
    default:
      break;
  }
  switch (StarterBot.GetStatus()) {
    case E_FORWARD:
      StarterBot.SetRgbColor(E_RGB_ALL, RGB_WHITE);
      break;
    case E_LEFT:
      StarterBot.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      break;
    case E_RIGHT:
      StarterBot.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      break;
    case E_BACK:
      StarterBot.SetRgbColor(E_RGB_ALL, RGB_RED);
      break;
    case E_STOP:
      StarterBot.SetRgbColor(E_RGB_ALL, RGB_OFF);
      break;
    case E_SPEED_UP:
      StarterBot.SetRgbColor(E_RGB_ALL, StarterBot.GetSpeed() * 2.5);
      break;
    case E_SPEED_DOWN:
      StarterBot.SetRgbColor(E_RGB_ALL, StarterBot.GetSpeed() * 2.5);
      break;
    default:
      break;
  }
}
