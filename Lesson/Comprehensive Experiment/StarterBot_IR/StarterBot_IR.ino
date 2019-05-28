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

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_INFRARED_REMOTE_CONTROL);
  StarterBot.IrInit();
  StarterBot.SetUltrasonicPin( UL_ECHO_PIN,UL_TRIG_PIN , SERVO_PIN);
  StarterBot.SetSpeed(0);
  StarterBot.mUltrasonic->SetServoBaseDegree(90);
  StarterBot.mUltrasonic->SetServoDegree(90);
}

void HandleInfaredRemote(byte irKeyCode)
{
  switch ((E_IR_KEYCODE)StarterBot.mIrRecv->getIrKey(irKeyCode)) 
  {
    case IR_KEYCODE_STAR:
      StarterBot.SpeedUp(10);
      DEBUG_LOG(DEBUG_LEVEL_INFO, "StarterBot.Speed = %d \n", StarterBot.Speed);
      break;
    case IR_KEYCODE_POUND:
      DEBUG_LOG(DEBUG_LEVEL_INFO, " start Degree = %d \n", StarterBot.Degree);
      StarterBot.SpeedDown(10);
      break;
    case IR_KEYCODE_UP:
      StarterBot.GoForward();
      break;
    case IR_KEYCODE_DOWN:
      StarterBot.GoBack();
      break;
    case IR_KEYCODE_OK:
      StarterBot.KeepStop();
      break;
    case IR_KEYCODE_LEFT:
      StarterBot.TurnLeft();
      break;
    case IR_KEYCODE_RIGHT:
      StarterBot.TurnRight();
      break;
    default:
      break;
  }
}

void loop()
{
  switch (StarterBot.GetControlMode()) {
    
    case E_INFRARED_REMOTE_CONTROL:
      byte irKeyCode;
      if (irKeyCode = StarterBot.mIrRecv->getCode()) 
      {
       
        DEBUG_LOG(DEBUG_LEVEL_INFO, "irKeyCode = %lx \n", irKeyCode);
        HandleInfaredRemote(irKeyCode);
        delay(110);
      }
      else {
        if (StarterBot.GetStatus() != E_STOP ) {
          StarterBot.KeepStop();
        }
      }
      break;
    default:
      break;
  }
}
