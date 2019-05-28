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

#define IR_TRACING_PIN1 A0
#define IR_TRACING_PIN2 A1
#define IR_TRACING_PIN3 A2

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
   StarterBot.SetControlMode(E_ULTRASONIC_INFRARED_AVOIDANCE);
   StarterBot.SetUltrasonicPin(UL_ECHO_PIN, UL_TRIG_PIN, SERVO_PIN);
   StarterBot.SetPhotoInfraredAvoidancePin(IR_AVOIDANCE_LEFT_PIN, IR_AVOIDANCE_RIGHT_PIN, PHOTOSENSITIVE_LEFT_PIN, PHOTOSENSITIVE_RIGHT_PIN);
   StarterBot.SetSpeed(0);
   StarterBot.mUltrasonic->SetServoBaseDegree(90);
   StarterBot.mUltrasonic->SetServoDegree(90);

}
void HandleUltrasonicInfraredAvoidance(void)
{
  uint16_t RightValue, LeftValue;
  uint16_t UlFrontDistance, UlLeftDistance, UlRightDistance;
  LeftValue =  StarterBot.GetInfraredAvoidanceValue(0);
  RightValue =  StarterBot.GetInfraredAvoidanceValue(1);
  UlFrontDistance =   StarterBot.GetUltrasonicValue(FRONT);
  Serial.println(UlFrontDistance);
  delay(20);
  DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n", UlFrontDistance);
  if ((RightValue != IA_THRESHOLD) && (LeftValue == IA_THRESHOLD))
  {
     StarterBot.SetSpeed(70);
     StarterBot.Drive(20);
  }
  else if ((RightValue == IA_THRESHOLD) && (LeftValue != IA_THRESHOLD))
  {
     StarterBot.SetSpeed(70);
     StarterBot.Drive(160);
  }
  else
  {
     StarterBot.SetSpeed(45);
     StarterBot.GoForward();
  }
  DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance = %d \n\r", UlFrontDistance);
  if (UlFrontDistance < UL_LIMIT_MID) 
  {
     StarterBot.KeepStop();
    if ((UlFrontDistance <= UL_LIMIT_MIN)|| (RightValue == IA_THRESHOLD && LeftValue == IA_THRESHOLD)) 
    {
       StarterBot.SetSpeed(60);
       StarterBot.GoBack();
      delay(300);
       StarterBot.KeepStop();
    }
    UlLeftDistance =  StarterBot.GetUltrasonicValue(LEFT);
    UlRightDistance =  StarterBot.GetUltrasonicValue(RIGHT);
    if (UlRightDistance >= UlLeftDistance) {
       StarterBot.SetSpeed(80);
       StarterBot.TurnRight();
      delay(200);
    }
    else if (UlLeftDistance > UlRightDistance) {
       StarterBot.SetSpeed(80);
       StarterBot.TurnLeft();
      delay(200);
    }
    else if (UlLeftDistance <= UL_LIMIT_MIN && UlRightDistance <= UL_LIMIT_MIN ) {
       StarterBot.SetSpeed(80);
       StarterBot.Drive(0);
      delay(400);
       StarterBot.KeepStop();
    }
     StarterBot.KeepStop();
  }
}

void loop()
{
  switch ( StarterBot.GetControlMode()) {
    case E_ULTRASONIC_INFRARED_AVOIDANCE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_INFRARED_AVOIDANCE \n");
      HandleUltrasonicInfraredAvoidance();
      break;
    default:
      break;
  }
}
