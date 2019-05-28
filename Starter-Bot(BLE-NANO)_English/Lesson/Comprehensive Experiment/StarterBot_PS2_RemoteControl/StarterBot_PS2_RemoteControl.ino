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
#define PS2X_CLK 11
#define PS2X_CMD 7
#define PS2X_CS  8
#define PS2X_DAT 4

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);
byte Ps2xStatus, Ps2xType;

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_PS2_REMOTE_CONTROL);
  StarterBot.SetUltrasonicPin( UL_ECHO_PIN,UL_TRIG_PIN , SERVO_PIN);
  StarterBot.SetPs2xPin(PS2X_CLK, PS2X_CMD, PS2X_CS, PS2X_DAT);
  StarterBot.SetSpeed(0);
  Ps2xType = StarterBot.mPs2x->readType();
}

void HandlePS2()
{
  static int vibrate = 0;
  byte PSS_X = 0, PSS_Y = 0;
  StarterBot.mPs2x->read_gamepad(false, vibrate); // read controller and set large motor to spin at 'vibrate' speed
  if (StarterBot.mPs2x->ButtonDataByte()) {
    if (StarterBot.mPs2x->Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
      StarterBot.GoForward();
    }
    if (StarterBot.mPs2x->Button(PSB_PAD_RIGHT)) {
      StarterBot.Drive(20);
    }
    if (StarterBot.mPs2x->Button(PSB_PAD_LEFT)) {
      StarterBot.Drive(160);
    }
    if (StarterBot.mPs2x->Button(PSB_PAD_DOWN)) {
      StarterBot.GoBack();
    }
    vibrate = StarterBot.mPs2x->Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (StarterBot.mPs2x->Button(PSB_CROSS)) {             //will be TRUE if button was JUST pressed OR released
      StarterBot.SpeedDown(5);
    }
    if (StarterBot.mPs2x->Button(PSB_TRIANGLE)) {
      StarterBot.SpeedUp(5);
    }
    if (StarterBot.mPs2x->Button(PSB_SQUARE)) {
      StarterBot.TurnLeft();
    }
    if (StarterBot.mPs2x->Button(PSB_CIRCLE)) {
      StarterBot.TurnRight();
    }
    if (StarterBot.mPs2x->Button(PSB_L1) || StarterBot.mPs2x->Button(PSB_R1)) {
      uint16_t RightValue = StarterBot.mPs2x->RightHart();
      uint16_t LeftValue = StarterBot.mPs2x->LeftHart();
      if (RightValue != CENTER) {
        if ((RightValue > 0) && (RightValue < 180 )) {
          StarterBot.SpeedUp(2);
        } else {
          StarterBot.SpeedDown(2);
        }
      }
      if (LeftValue != CENTER) {
        StarterBot.Drive(LeftValue);
      } else {
        StarterBot.KeepStop();
      }
    }
  }
  else {
    StarterBot.KeepStop();
  }
  delay(50);
}

void loop()
{
  switch (StarterBot.GetControlMode()) {
    case E_PS2_REMOTE_CONTROL:
      while (Ps2xStatus != 0) { //skip loop if no controller found
        delay(500);
        Ps2xStatus = StarterBot.ResetPs2xPin();
        Ps2xType = StarterBot.mPs2x->readType();
        DEBUG_LOG(DEBUG_LEVEL_INFO, "E_PS2_REMOTE_CONTROL \n");
      }
      if (Ps2xType != 2) {
        HandlePS2();
      }
      break;
    default:
      break;
  }
}
