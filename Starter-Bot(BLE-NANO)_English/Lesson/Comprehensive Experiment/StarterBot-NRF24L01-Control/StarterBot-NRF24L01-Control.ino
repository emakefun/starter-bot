#include "StarterBot.h"
#include "BluetoothHandle.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  ---  right
#define IN3_PIN 5   // DIRA  ---  left
#define IN4_PIN 9   // PWMA

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);

void setup()
{
  Serial.begin(9600);
  StarterBot.init();
  StarterBot.SetControlMode(E_NRF24L01_CONTROL);
  StarterBot.SetNrf24L01Pin();
  StarterBot.SetSpeed(0);
}

void HandleNrf24L01Remote()
{
  byte value[12] = {0};
  bool godata = false;
  if ( StarterBot.mNrf24L01->dataReady()) { //When the program is received, the received data is output from the serial port
    StarterBot.mNrf24L01->getData(value);
    for (int i = 0; i < 12; i++) {
      Serial.print(value[i], HEX); Serial.print(" ");
    }
    Serial.println("");
    mProtocol->RecevData(value, 12);
  }
  if (mProtocol->ParserPackage())
  {
    Serial.println("test");
    switch (mProtocol->GetRobotControlFun()) {
      case E_ROBOT_CONTROL_DIRECTION:
        DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ROBOT_CONTROL_DIRECTION \n");
        StarterBot.Drive(mProtocol->GetRobotDegree());
        break;
      case E_ROBOT_CONTROL_SPEED:
        DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ROBOT_CONTROL_SPEED \n");
        StarterBot.SetSpeed(mProtocol->GetRobotSpeed());
        break ;
      default:
        break;
    }
  }
}

void loop()
{
  static byte mode;
  static bool recv_flag;
  switch (StarterBot.GetControlMode())
  {
    case E_NRF24L01_CONTROL:
      HandleNrf24L01Remote();
      // DEBUG_LOG(DEBUG_LEVEL_INFO, "E_NRF24L01_CONTROL \n");
      break;
    default:
      break;
  }
 
}
