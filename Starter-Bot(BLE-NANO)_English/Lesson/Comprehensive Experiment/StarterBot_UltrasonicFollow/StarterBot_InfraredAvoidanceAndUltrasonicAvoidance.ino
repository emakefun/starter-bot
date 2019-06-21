#include "StarterBot.h"
#include "BluetoothHandle.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  --- left
#define IN3_PIN 5   // DIRA  --- right 
#define IN4_PIN 9   // PWMA

#define IR_PIN 11
#define SERVO_PIN 13
#define UL_ECHO_PIN 3
#define UL_TRIG_PIN 2


#define PHOTOSENSITIVE_LEFT_PIN A3
#define PHOTOSENSITIVE_RIGHT_PIN A4
#define IR_AVOIDANCE_LEFT_PIN 12
#define IR_AVOIDANCE_RIGHT_PIN A5

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot  StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup()
{
  Serial.begin(9600);
   StarterBot.init();
   StarterBot.SetControlMode(E_ULTRASONIC_FOLLOW_MODE);
   StarterBot.SetUltrasonicPin(UL_ECHO_PIN, UL_TRIG_PIN, SERVO_PIN);
   StarterBot.SetPhotoInfraredAvoidancePin(IR_AVOIDANCE_LEFT_PIN, IR_AVOIDANCE_RIGHT_PIN, PHOTOSENSITIVE_LEFT_PIN, PHOTOSENSITIVE_RIGHT_PIN);
   StarterBot.SetSpeed(0);
   StarterBot.mUltrasonic->SetServoBaseDegree(90);
   StarterBot.mUltrasonic->SetServoDegree(90);

}
void UltrasonicFollow()
{
  uint16_t RightValue, LeftValue,UlFrontDistance;
   
  LeftValue =  StarterBot.GetInfraredAvoidanceValue(0);
  RightValue =  StarterBot.GetInfraredAvoidanceValue(1);
  UlFrontDistance =   StarterBot.GetUltrasonicValue(FRONT); 
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
  switch ( StarterBot.GetControlMode()) {
    case E_ULTRASONIC_FOLLOW_MODE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_INFRARED_AVOIDANCE \n");
       UltrasonicFollow();
      break;
    default:
      break;
  }
}
