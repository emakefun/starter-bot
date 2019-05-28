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

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_BLUETOOTH_CONTROL);
  StarterBot.SetUltrasonicPin( UL_ECHO_PIN,UL_TRIG_PIN , SERVO_PIN);
  StarterBot.SetSpeed(0);
  StarterBot.mUltrasonic->SetServoBaseDegree(90);
  StarterBot.mUltrasonic->SetServoDegree(90);
}

void HandleBluetoothRemote(bool recv_flag)
{
  if (recv_flag) {
    switch (mProtocol->GetRobotControlFun()) {
      case E_BUTTON:
        switch (mProtocol->GetBluetoothButton())
        {
          case BT_PAD_UP:
            StarterBot.GoForward();
            break;
          case BT_PAD_DOWN:
            StarterBot.GoBack();
            break;
          case BT_PAD_LEFT:
            StarterBot.TurnLeft();
            break;
          case BT_PAD_RIGHT:
            StarterBot.TurnRight();
            break;
        }
        break;
      case E_ROBOT_CONTROL_DIRECTION:
        StarterBot.Drive(mProtocol->GetRobotDegree());
        break;
      case E_ROBOT_CONTROL_SPEED:
        StarterBot.SetSpeed(mProtocol->GetRobotSpeed());
        break ;
      case E_CONTROL_MODE:
        //Serial.println(mProtocol->GetControlMode());
        StarterBot.SetControlMode(mProtocol->GetControlMode());
        break;
      case E_VERSION:
        StarterBot.SendVersionPackage();
        break;
      case E_SERVER_DEGREE:
        StarterBot.mUltrasonic->SetServoDegree(mProtocol->GetServoDegree());
        break;

    }
  }
}

void loop()
{
  static byte mode;
  static bool recv_flag;
  mProtocol->RecevData();
  if (recv_flag = mProtocol->ParserPackage()) {
    if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
      StarterBot.SetControlMode(mProtocol->GetControlMode());
      return;
    }
  }
  switch (StarterBot.GetControlMode()) {
    case E_BLUETOOTH_CONTROL:
      HandleBluetoothRemote(recv_flag);
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
      break;
    default:
      break;
  }
}
