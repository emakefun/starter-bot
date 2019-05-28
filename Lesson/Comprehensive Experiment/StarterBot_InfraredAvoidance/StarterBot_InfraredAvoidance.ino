#include "StarterBot.h"
#include "BluetoothHandle.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  --- left Motor control pins
#define IN3_PIN 5   // DIRA  --- right Motor control pins
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
   StarterBot.SetControlMode(E_INFRARED_AVOIDANCE_MODE);
   StarterBot.SetUltrasonicPin( UL_ECHO_PIN,UL_TRIG_PIN , SERVO_PIN);
   StarterBot.SetPhotoInfraredAvoidancePin(IR_AVOIDANCE_LEFT_PIN, IR_AVOIDANCE_RIGHT_PIN, PHOTOSENSITIVE_LEFT_PIN, PHOTOSENSITIVE_RIGHT_PIN);
   StarterBot.SetSpeed(0);
  StarterBot.mUltrasonic->SetServoBaseDegree(90);
   StarterBot.mUltrasonic->SetServoDegree(90);
}
//**********************************************************************
// Name : HandleInfraredAvoidance
//Function : infrared obstacle avoidance
//Parameter:null
//**********************************************************************

void HandleInfraredAvoidance()
{
  uint16_t RightValue, LeftValue; 
  LeftValue =  StarterBot.GetInfraredAvoidanceValue(0);
  RightValue =  StarterBot.GetInfraredAvoidanceValue(1);
  if ((RightValue != IA_THRESHOLD) && (LeftValue == IA_THRESHOLD))//Obstacles detected on both left
  {
       StarterBot.SetSpeed(80);
       StarterBot.TurnRight();
      delay(200);
  }
  else if ((RightValue == IA_THRESHOLD) && (LeftValue != IA_THRESHOLD))//Obstacles detected on both right
  {
       StarterBot.SetSpeed(80);
       StarterBot.TurnLeft();
      delay(200);
  }
  else if((RightValue == IA_THRESHOLD) && (LeftValue == IA_THRESHOLD)) //Obstacles were detected on both sides
  {
    StarterBot.SetSpeed(45);
     StarterBot.GoBack();
    delay(300);
  }
  else if ((RightValue != IA_THRESHOLD) && (LeftValue != IA_THRESHOLD)) //No obstacles were detected on either side
  {   
      StarterBot.SetSpeed(45);
     StarterBot.GoForward();
   }  
}


void loop()
{
  static bool recv_flag;
  mProtocol->RecevData();
  if (recv_flag = mProtocol->ParserPackage()) {
    if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
       StarterBot.SetControlMode(mProtocol->GetControlMode());
      return;
    }
  }
  switch ( StarterBot.GetControlMode()) {
    case E_INFRARED_AVOIDANCE_MODE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
      HandleInfraredAvoidance();
      break;
    default:
      break;
  }
}
