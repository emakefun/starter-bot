#include "StarterBot.h"
#include "BluetoothHandle.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  --- left Motor control pins
#define IN3_PIN 5   // DIRA  --- right Motor control pins
#define IN4_PIN 9   // PWMA

#define SERVO_PIN 13
#define UL_SING_PIN 3
#define UL_RGB_PIN 2

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_ULTRASONIC_AVOIDANCE);//E_BLUETOOTH_CONTROL/E_INFRARED_TRACKING_MODE
  StarterBot.SetRgbUltrasonicPin(UL_SING_PIN, UL_RGB_PIN, SERVO_PIN);
  StarterBot.SetSpeed(0);
  StarterBot.mRgbUltrasonic->SetServoBaseDegree(90);
  StarterBot.mRgbUltrasonic->SetServoDegree(90);

}

void HandleUltrasonicAvoidance(void)
{
  uint16_t UlFrontDistance, UlLeftDistance, UlRightDistance;
  UlFrontDistance =  StarterBot.GetUltrasonicValue(FRONT);
  DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n", UlFrontDistance);
  
  Serial.print("UlFrontDistance=====");
  Serial.println(UlFrontDistance);
  if ((UlFrontDistance < UL_LIMIT_MIN))
  {
    StarterBot.SetSpeed(80);
    StarterBot.GoBack();
    delay(250);
    Serial.println("==UlFrontDistance < UL_LIMIT_MIN==");
  }
  else if (UlFrontDistance < UL_LIMIT_MID)
  {
    StarterBot.KeepStop();
    delay(100);
    UlLeftDistance =  StarterBot.GetUltrasonicValue(LEFT);
    UlRightDistance =  StarterBot.GetUltrasonicValue(RIGHT);
    if ((UlRightDistance > UL_LIMIT_MIN) && (UlRightDistance < UL_LIMIT_MAX) && (UlLeftDistance > UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MAX))
    {
      if (UlRightDistance > UlLeftDistance)
      {
         StarterBot.SetSpeed(80);
         StarterBot.TurnRight();
        delay(310);
      }
      else
      {
         StarterBot.SetSpeed(80);
         StarterBot.TurnLeft();
        delay(310);
        
        
      }
    }
    else if (((UlRightDistance > UL_LIMIT_MIN) && (UlRightDistance < UL_LIMIT_MAX)) || ((UlLeftDistance > UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MAX)))
    {
      if ((UlLeftDistance > UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MAX))
      {
         StarterBot.SetSpeed(80);
         StarterBot.TurnLeft();
        delay(310);
      }
      else if ((UlRightDistance > UL_LIMIT_MIN) && (UlRightDistance < UL_LIMIT_MAX))
      {
         StarterBot.SetSpeed(80);
         StarterBot.TurnRight();
        delay(310);
        
      }
    }
    else if ((UlRightDistance < UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MIN) )
    {
      StarterBot.SetSpeed(80);
      StarterBot.Drive(0);
      delay(510);
     
    }
  } 
  else 
  {
    StarterBot.SetSpeed(60);
    StarterBot.GoForward();
     
  }
}

void loop()
{
  switch (StarterBot.GetControlMode()) {
    case E_ULTRASONIC_AVOIDANCE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_AVOIDANCE \n");
      HandleUltrasonicAvoidance();
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
      //   Mirage.Sing(S_OhOoh);
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
