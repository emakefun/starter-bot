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
#define UL_ECHO_PIN 3
#define UL_TRIG_PIN 2

#define PHOTOSENSITIVE_LEFT_PIN A3
#define PHOTOSENSITIVE_RIGHT_PIN A4
#define IR_AVOIDANCE_LEFT_PIN 12
#define IR_AVOIDANCE_RIGHT_PIN A5

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_LIGHT_SEEKING_MODE);
  StarterBot.SetUltrasonicPin( UL_ECHO_PIN,UL_TRIG_PIN , SERVO_PIN);
  StarterBot.SetPhotoInfraredAvoidancePin(IR_AVOIDANCE_LEFT_PIN, IR_AVOIDANCE_RIGHT_PIN, PHOTOSENSITIVE_LEFT_PIN, PHOTOSENSITIVE_RIGHT_PIN);
  StarterBot.SetSpeed(0);
}

void HandleLightSeeking()
{
  float LeftValue, RightValue;
  int Angle;
  StarterBot.SetSpeed(80);
  LeftValue = StarterBot.GetPhotosensitive(0)/10;
  RightValue = StarterBot.GetPhotosensitive(1)/10;
  if ((LeftValue > 30) && (RightValue > 30))
  {
    StarterBot.KeepStop();
  } else {
    if (LeftValue >= RightValue) {
      Angle = ((float)(RightValue/LeftValue) * 90);
    } else if (LeftValue < RightValue) {
      Angle = (180 - ((float)(LeftValue / RightValue)) * 90);
    }
    StarterBot.Drive(Angle);
  }
}

void loop()
{

  switch (StarterBot.GetControlMode()) {
    case E_LIGHT_SEEKING_MODE:
      HandleLightSeeking();
      StarterBot.SendPhotoresistorData();
      break;
    default:
      break;
  }
}
