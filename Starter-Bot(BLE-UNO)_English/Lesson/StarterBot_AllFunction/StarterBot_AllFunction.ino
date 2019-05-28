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
#define UL_SING_PIN 3
#define UL_RGB_PIN 2
#define PS2X_CLK 11
#define PS2X_CMD 7
#define PS2X_CS  8
#define PS2X_DAT 4
#define IR_TRACING_PIN1 A2
#define IR_TRACING_PIN2 A1
#define IR_TRACING_PIN3 A0

#define PHOTOSENSITIVE_LEFT_PIN A3
#define PHOTOSENSITIVE_RIGHT_PIN A4
#define IR_AVOIDANCE_LEFT_PIN 12
#define IR_AVOIDANCE_RIGHT_PIN A5

ProtocolParser *mProtocol = new ProtocolParser();
StarterBot StarterBot(mProtocol, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN);
byte Ps2xStatus, Ps2xType;

void setup()
{
  Serial.begin(9600);
  StarterBot.init();  //motor initialization
  StarterBot.SetControlMode(E_BLUETOOTH_CONTROL);//set default  mode is bluetooth remote mode
  StarterBot.SetSpeed(0);
  StarterBot.SetInfraredTracingPin(IR_TRACING_PIN1, IR_TRACING_PIN2, IR_TRACING_PIN3);
  StarterBot.SetPhotoInfraredAvoidancePin(IR_AVOIDANCE_LEFT_PIN, IR_AVOIDANCE_RIGHT_PIN, PHOTOSENSITIVE_LEFT_PIN, PHOTOSENSITIVE_RIGHT_PIN);
  StarterBot.SetRgbUltrasonicPin(UL_SING_PIN, UL_RGB_PIN, SERVO_PIN);
  StarterBot.mRgbUltrasonic->ServoPIN(SERVO_PIN);
  Ps2xType = StarterBot.mPs2x->readType();
  StarterBot.mRgbUltrasonic->SetServoBaseDegree(90);
  StarterBot.mRgbUltrasonic->SetServoDegree(90);

}

//**********************************************************************************************
// Name : HandleUltrasonicInfraredAvoidance
//Function : Ultrasonic and infrared obstacle avoidance
//Parameter:null
//**********************************************************************************************
void HandleUltrasonicInfraredAvoidance(void)
{
  uint16_t RightValue, LeftValue;                                   //define  variable save the infrared obstacle avoidance value
  uint16_t UlFrontDistance, UlLeftDistance, UlRightDistance;        //define  variable save the ultrasonic obstacle avoidance value
  LeftValue = StarterBot.GetInfraredAvoidanceValue(0);
  RightValue = StarterBot.GetInfraredAvoidanceValue(1);
  UlFrontDistance =  StarterBot.GetUltrasonicValue(FRONT);
  delay(20);
  DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n", UlFrontDistance);
  StarterBot.SendInfraredAvoidanceData();
  StarterBot.SendUltrasonicData();   
  if ((RightValue != IA_THRESHOLD) && (LeftValue == IA_THRESHOLD))
  {
    StarterBot.SetSpeed(70);
    StarterBot.Drive(20);
     DEBUG_LOG(DEBUG_LEVEL_INFO, "(RightValue != IA_THRESHOLD) && (LeftValue == IA_THRESHOLD) =%d \n", IA_THRESHOLD);
  }
  else if ((RightValue == IA_THRESHOLD) && (LeftValue != IA_THRESHOLD))
  {
    StarterBot.SetSpeed(70);
    StarterBot.Drive(160);
     DEBUG_LOG(DEBUG_LEVEL_INFO, "(RightValue != IA_THRESHOLD) && (LeftValue == IA_THRESHOLD) =%d \n", IA_THRESHOLD);
  }
  else
  {
    StarterBot.SetSpeed(45);
    StarterBot.GoForward();
  } 
  if (UlFrontDistance < UL_LIMIT_MID) 
  {
    StarterBot.KeepStop();
    if (UlFrontDistance <= UL_LIMIT_MIN || (RightValue == IA_THRESHOLD && LeftValue == IA_THRESHOLD))
    {
      StarterBot.SetSpeed(50);
      StarterBot.GoBack();
      delay(300);
      StarterBot.KeepStop();
    }
    UlLeftDistance = StarterBot.GetUltrasonicValue(LEFT);
    UlRightDistance = StarterBot.GetUltrasonicValue(RIGHT);
    if (UlLeftDistance <= UL_LIMIT_MIN && UlRightDistance <= UL_LIMIT_MIN ) 
    {
      StarterBot.SetSpeed(80);
      StarterBot.Drive(0);
      delay(200);
      StarterBot.KeepStop();
    }
    else if (UlRightDistance >= UlLeftDistance)
    {
      StarterBot.SetSpeed(80);
      StarterBot.TurnRight();
      delay(200);
    }
    else if (UlLeftDistance > UlRightDistance)
    {
      StarterBot.SetSpeed(60);
      StarterBot.TurnLeft();
      delay(200);
    }
     StarterBot.KeepStop();
  }
  else
  {
    StarterBot.SetSpeed(45);
    StarterBot.GoForward();
  }
}
//**********************************************************************************************
// Name : HandleUltrasonicAvoidance
//Function : Ultrasonic obstacle avoidance
//Parameter:null
//**********************************************************************************************
void HandleUltrasonicAvoidance(void)
{
  uint16_t UlFrontDistance, UlLeftDistance, UlRightDistance;
  UlFrontDistance =  StarterBot.GetUltrasonicValue(FRONT);
  delay(20);
  DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n", UlFrontDistance);
  if ((UlFrontDistance < UL_LIMIT_MIN))
  {
    StarterBot.SetSpeed(80);
    StarterBot.GoBack();
    delay(250);
  }
  else if (UlFrontDistance < UL_LIMIT_MID)
  {
    StarterBot.KeepStop();
    delay(100);
    UlLeftDistance = StarterBot.GetUltrasonicValue(LEFT);
    UlRightDistance = StarterBot.GetUltrasonicValue(RIGHT);
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

//**********************************************************************************************
//Name : HandleInfraredTracing
//Function : Infrared Tracing
//Parameter:null
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
        while (StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
          StarterBot.SetSpeed(40);
          StarterBot.Drive(180);
        }
        old = 0;
        break;
      } if (old == IT_LEFT1) {
        while (StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
          StarterBot.SetSpeed(40);
          StarterBot.Drive(0);
        }
        old = 0;
        break;
      }  if (old == IT_RIGHT2) {
        while (StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
          StarterBot.SetSpeed(40);
          StarterBot.Drive(160);
        }
        old = 0;
        break;
      } if (old == IT_LEFT2) {
        while (StarterBot.mInfraredTracing->GetValue() == IT_ALL_WHITE) {
          StarterBot.SetSpeed(40);
          StarterBot.Drive(20);
        }
        old = 0;
        break;
      }
      StarterBot.KeepStop();
      break;
    case IT_CENTER:
      StarterBot.SetSpeed(45);
      StarterBot.GoForward();
      break;
    case IT_RIGHT1:
      StarterBot.SetSpeed(50);
      StarterBot.Drive(180);
      old = IT_RIGHT1;
      break;
    case IT_RIGHT2:
      StarterBot.SetSpeed(40);
      StarterBot.Drive(160);
      old = IT_RIGHT2;
      break;
    case IT_LEFT1:
      StarterBot.SetSpeed(50);
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
//**********************************************************************************************
//Name : HandleBluetoothRemote
//Function : Bluetooth Remote control
//Parameter:null
//**********************************************************************************************
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
      case E_LED:
        StarterBot.SetRgbColor(E_RGB_ALL, mProtocol->GetRgbValue());
        break;
      case E_VERSION:
        StarterBot.SendVersionPackage();
        break;
      case E_SERVER_DEGREE:
        StarterBot.mRgbUltrasonic->SetServoDegree(mProtocol->GetServoDegree());
        break;
    }
  }
}

//**********************************************************************************************
//Name : HandleInfaredRemote
//Function : Infared Remote control
//Parameter:irKeyCode
//**********************************************************************************************
void HandleInfaredRemote(byte irKeyCode)
{
  switch ((E_IR_KEYCODE)StarterBot.mIrRecv->getIrKey(irKeyCode)) {
    case IR_KEYCODE_PLUS:
      StarterBot.SpeedUp(10);
      DEBUG_LOG(DEBUG_LEVEL_INFO, "StarterBot.Speed = %d \n", StarterBot.Speed);
      break;
    case IR_KEYCODE_REDUCE:
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

//**********************************************************************************************
//Name : HandleInfraredAvoidance
//Function : Infrared Avoidance
//Parameter:Null
//**********************************************************************************************
void HandleInfraredAvoidance()
{
  uint16_t RightValue, LeftValue;
  LeftValue = StarterBot.GetInfraredAvoidanceValue(0);
  RightValue = StarterBot.GetInfraredAvoidanceValue(1);
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
  else if ((RightValue == IA_THRESHOLD) && (LeftValue == IA_THRESHOLD)) //Obstacles were detected on both sides
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

//**********************************************************************************************
//Name : HandleLightSeeking
//Function : Light Seeking
//Parameter:Null
//**********************************************************************************************
void HandleLightSeeking(void)
{
  float LeftValue, RightValue;
  int Angle;
  StarterBot.SetSpeed(80);
  LeftValue = StarterBot.GetPhotosensitive(0) / 10;
  RightValue = StarterBot.GetPhotosensitive(1) / 10;
  if ((LeftValue > 30) && (RightValue > 30))
  {
    StarterBot.KeepStop();
  } else {
    if (LeftValue >= RightValue) {
      Angle = ((float)(RightValue / LeftValue) * 90);
    } else if (LeftValue < RightValue) {
      Angle = (180 - ((float)(LeftValue / RightValue)) * 90);
    }
    StarterBot.Drive(Angle);
  }
}
//**********************************************************************************************
//Name : HandlePS2
//Function : PS2 Remote Control
//Parameter:Null
//**********************************************************************************************
void HandlePS2(void)
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
//**********************************************************************************************
//Name : UltrasonicFollow
//Function : Ultrasonic Follow
//Parameter:Null
//**********************************************************************************************
void UltrasonicFollow(void )
{
  StarterBot.SetSpeed(40);
  uint16_t UlFrontDistance =  StarterBot.GetUltrasonicValue(FRONT);
 // Serial.println(UlFrontDistance);
  delay(10);
  if (UlFrontDistance < 13) {
    StarterBot.GoBack();
  } else if (UlFrontDistance > 16) {
    StarterBot.GoForward();
  } else if (13 <= UlFrontDistance <=16) {
    StarterBot.KeepStop();
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
    case E_INFRARED_REMOTE_CONTROL:
      if (mode != E_INFRARED_REMOTE_CONTROL) 
      {
        StarterBot.IrInit();
        mode= E_INFRARED_REMOTE_CONTROL;
      }
      byte irKeyCode;
      if (irKeyCode = StarterBot.mIrRecv->getCode()) {
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
    case E_INFRARED_TRACKING_MODE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_TRACKING \n");    
      StarterBot.SendInfraredTracking();
      HandleInfraredTracing();
      break;
    case E_INFRARED_AVOIDANCE_MODE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
      StarterBot.SendInfraredAvoidanceData();
      HandleInfraredAvoidance();
      break;
    case E_LIGHT_SEEKING_MODE:
      HandleLightSeeking();
      StarterBot.SendPhotoresistorData();
      break;
    case E_ULTRASONIC_AVOIDANCE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_AVOIDANCE \n");
      StarterBot.SendUltrasonicData();
      HandleUltrasonicAvoidance();
      break;
    case E_ULTRASONIC_INFRARED_AVOIDANCE:
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_INFRARED_AVOIDANCE \n");
      HandleUltrasonicInfraredAvoidance();    
      break;
    case E_PS2_REMOTE_CONTROL:
    if (mode != E_PS2_REMOTE_CONTROL)
    {
       StarterBot.SetPs2xPin(PS2X_CLK, PS2X_CMD, PS2X_CS, PS2X_DAT);
        mode = E_PS2_REMOTE_CONTROL;
      }   
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
    case E_ULTRASONIC_FOLLOW_MODE:
        DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_FOLLOW_MODE \n");
        UltrasonicFollow();
        break;
    case E_RGB_MODE:
      if (recv_flag) {
        if (mProtocol->GetRobotControlFun() == E_LED) {
          if (mProtocol->GetRgbMode() == 1) {
              StarterBot.SetRgbColor(E_RGB_ALL, mProtocol->GetRgbValue());
          } else {
              StarterBot.SetRgbEffect(E_RGB_ALL, mProtocol->GetRgbValue(), mProtocol->GetRgbEffect());
          }
        }
      }
      return;
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
      // Mirage.Sing(S_OhOoh);
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
