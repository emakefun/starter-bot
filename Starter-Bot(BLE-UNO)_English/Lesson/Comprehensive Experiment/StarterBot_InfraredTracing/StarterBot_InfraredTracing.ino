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

#define IR_TRACING_PIN1 A2
#define IR_TRACING_PIN2 A1
#define IR_TRACING_PIN3 A0

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_INFRARED_TRACKING_MODE);
  StarterBot.SetInfraredTracingPin(IR_TRACING_PIN1, IR_TRACING_PIN2, IR_TRACING_PIN3);
  StarterBot.SetRgbUltrasonicPin(UL_SING_PIN, UL_RGB_PIN, SERVO_PIN);
  StarterBot.SetSpeed(0);
}
//**********************************************************************************************
//Name : HandleInfraredTracing
//Function : InfraredTracing
//Parameter:Null
//**********************************************************************************************
void HandleInfraredTracing(void)
{
  static byte old;
  switch (StarterBot.mInfraredTracing->GetValue()) {
    case IT_ALL_BLACK:
      StarterBot.KeepStop();
      break;
    case IT_ALL_WHITE:
      if (old == IT_RIGHT1) {
        while ( StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
           StarterBot.SetSpeed(60);
           StarterBot.Drive(180);
        }
        old = 0;
        break;
      } if (old == IT_LEFT1) {
        while ( StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
           StarterBot.SetSpeed(60);
           StarterBot.Drive(0);
        }
        old = 0;
        break;
      }  if (old == IT_RIGHT2) {
        while ( StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
           StarterBot.SetSpeed(40);
           StarterBot.Drive(160);
        }
        old = 0;
        break;
      } if (old == IT_LEFT2) {
        while ( StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
           StarterBot.SetSpeed(40);
           StarterBot.Drive(20);
        }
        old = 0;
        break;
      }
       StarterBot.KeepStop();
      break;
    case IT_CENTER:
       StarterBot.SetSpeed(40);
       StarterBot.GoForward();
      break;
    case IT_RIGHT1:
       StarterBot.SetSpeed(60);
       StarterBot.Drive(180);
      old = IT_RIGHT1;
      break;
    case IT_RIGHT2:
       StarterBot.SetSpeed(40);
       StarterBot.Drive(160);
      old = IT_RIGHT2;
      break;
    case IT_LEFT1:
       StarterBot.SetSpeed(60);
       StarterBot.Drive(0);
      old = IT_LEFT1;
      break;
    case IT_LEFT2:
       StarterBot.SetSpeed(40);
       StarterBot.Drive(20);
      old = IT_LEFT2;
      break;
  }
}

void loop()
{
  switch (StarterBot.GetControlMode()) {
    case E_INFRARED_TRACKING_MODE:  
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_TRACKING \n");
      HandleInfraredTracing();
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
