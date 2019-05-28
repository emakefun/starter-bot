#include "StarterBot.h"
#include "ProtocolParser.h"
#include "debug.h"

StarterBot::StarterBot(ProtocolParser *Package, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4): SmartCar("StarterBot", 0x01, E_BLUETOOTH_CONTROL)
{
  this->In1Pin = in1;
  this->In2Pin = in2;
  this->In3Pin = in3;
  this->In4Pin = in4;
  SetStatus(E_STOP);
  mProtocolPackage = Package;
  Speed = 0;
}

StarterBot::~StarterBot()
{
  delete mIrRecv;
  delete mPs2x;
  delete mInfraredTracing;
  delete mPhotoIrAvoidance;
  delete mUltrasonic;
}

#if ARDUINO > 10609
void StarterBot::SetMotorPin(uint8_t in1 = EM_IN1_PIN, uint8_t in2 = EM_IN2_PIN, uint8_t in3 = EM_IN3_PIN, uint8_t in4 = EM_IN4_PIN)
#else
void StarterBot::SetMotorPin(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
#endif
{
  this->In1Pin = in1;
  this->In2Pin = in2;
  this->In3Pin = in3;
  this->In4Pin = in4;
  pinMode(In1Pin, OUTPUT);
  digitalWrite(In1Pin, LOW);
  pinMode(In2Pin, OUTPUT);
  digitalWrite(In2Pin, LOW);
  pinMode(In3Pin, OUTPUT);
  digitalWrite(In3Pin, LOW);
  pinMode(In4Pin, OUTPUT);
  digitalWrite(In4Pin, LOW);
}

void StarterBot::init(void)
{
  pinMode(In1Pin, OUTPUT);
  digitalWrite(In1Pin, LOW);
  pinMode(In2Pin, OUTPUT);
  digitalWrite(In2Pin, LOW);
  pinMode(In3Pin, OUTPUT);
  digitalWrite(In3Pin, LOW);
  pinMode(In4Pin, OUTPUT);
  digitalWrite(In4Pin, LOW);
}

void StarterBot::GoForward(void)
{
  int value = (Speed / 10) * 25;
  DEBUG_LOG(DEBUG_LEVEL_INFO, "GoForward\n");
  SetStatus(E_FORWARD);
  analogWrite(In1Pin, LOW);
  analogWrite(In2Pin, value);
  analogWrite(In3Pin, value);
  analogWrite(In4Pin, LOW);
}

void StarterBot::GoBack(void)
{
  int value = (Speed / 10) * 25;
  DEBUG_LOG(DEBUG_LEVEL_INFO, "GoBack\n");
  SetStatus(E_BACK);
  analogWrite(In1Pin, value);
  analogWrite(In2Pin, LOW);
  analogWrite(In3Pin, LOW);
  analogWrite(In4Pin, value);
}

void StarterBot::KeepStop(void)
{
  DEBUG_LOG(DEBUG_LEVEL_INFO, "KeepStop\n");
  SetStatus(E_STOP);
  analogWrite(In1Pin, LOW);
  analogWrite(In2Pin, LOW);
  analogWrite(In3Pin, LOW);
  analogWrite(In4Pin, LOW);
}

void StarterBot::TurnLeft(void)
{
  int value = (Speed / 10) * 25.5; //app contol  StarterBot_speed is 0 ~ 100 ,pwm is 0~255
  DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnLeft =%d \n", value);
  analogWrite(In1Pin, value);
  analogWrite(In2Pin, LOW);
  analogWrite(In3Pin, value);
  analogWrite(In4Pin, LOW);
  SetStatus(E_LEFT);
}

void StarterBot::TurnRight(void)
{
  int value = (Speed / 10) * 25.5; //app contol  StarterBot_speed is 0 ~ 100 ,pwm is 0~255
  analogWrite(In1Pin, LOW);
  analogWrite(In2Pin, value);
  analogWrite(In3Pin, LOW);
  analogWrite(In4Pin, value);
  SetStatus(E_RIGHT);
}
void StarterBot::Drive(void)
{
  Drive(Degree);
}

#if ARDUINO > 10609
void StarterBot::Drive(int degree = 90)
#else
void StarterBot::Drive(int degree)
#endif
{
  Degree = degree;
  DEBUG_LOG(DEBUG_LEVEL_INFO, "degree = %d speed = %d\n", degree, Speed);
  int value = (Speed / 10) * 25.5;	 //app contol  StarterBot_speed is 0 ~ 100 ,pwm is 0~255
  float f;
  if (degree >= 0 && degree <= 90) {
    f = (float)(degree) / 90;
    analogWrite(In1Pin, LOW);
    analogWrite(In2Pin, value);
    analogWrite(In3Pin, (float)(value * f));
    analogWrite(In4Pin, LOW);
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnRight\n");
    SetStatus(E_RIGHT);
  } else if (degree > 90 && degree <= 180) {
    f = (float)(180 - degree) / 90;
    analogWrite (In1Pin, LOW);
    analogWrite(In2Pin, (float)(value * f));
    analogWrite(In3Pin, value);
    analogWrite(In4Pin, LOW);
    SetStatus(E_LEFT);
  } else if (degree > 180 && degree <= 270) {
    f = (float)(degree - 180) / 90;
    analogWrite(In1Pin, (float)(value * f));
    analogWrite(In2Pin, 0);
    analogWrite(In3Pin, 0);
    analogWrite(In4Pin, value);
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnLeft\n");
    SetStatus(E_LEFT);
  } else if (degree >= 270 && degree <= 360) {
    f = (float)(360 - degree) / 90;
    analogWrite(In1Pin, value);
    analogWrite(In2Pin, 0);
    analogWrite(In3Pin, 0);
    analogWrite(In4Pin, (float)(value * f));
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnRight\n");
    SetStatus(E_RIGHT);
  }
  else {
    KeepStop();
  }
}


void StarterBot::IrInit(void )
{
  IrPin = EM_IR_PIN;
  mIrRecv = new IRremote (11);
  mIrRecv->begin();  // Initialize the infrared receiver
}


#if ARDUINO > 10609
void StarterBot::SetInfraredTracingPin(uint8_t Pin1 = EM_INFRARED_TRACING_PIN1, uint8_t Pin2 = EM_INFRARED_TRACING_PIN2, uint8_t Pin3 = EM_INFRARED_TRACING_PIN3)
#else
void StarterBot::SetInfraredTracingPin(uint8_t Pin1, uint8_t Pin2, uint8_t Pin3)
#endif
{
  static bool InfraredTracingInit = false;
  if (!InfraredTracingInit) {
    InfraredTracingPin1 = Pin1;
    InfraredTracingPin2 = Pin2;
    InfraredTracingPin3 = Pin3;
    mInfraredTracing = new InfraredTracing(InfraredTracingPin1, InfraredTracingPin2, InfraredTracingPin3);
    //mInfraredTracing->begin();
    InfraredTracingInit = true;
  }
}

#if ARDUINO > 10609
int StarterBot::SetPs2xPin(uint8_t clk = EM_PS2X_CLK, uint8_t cmd = EM_PS2X_CMD, uint8_t att = EM_PS2X_ATT, uint8_t dat = EM_PS2X_DAT)
#else
int StarterBot::SetPs2xPin(uint8_t clk , uint8_t cmd , uint8_t att , uint8_t dat)
#endif
{
  static bool Ps2xInit = false;
  int error = 0 ;
  if (!Ps2xInit) {
    DEBUG_LOG(DEBUG_LEVEL_INFO, "SetPs2xPin\n");
    Ps2xClkPin = clk;
    Ps2xCmdPin = cmd;
    Ps2xAttPin = att;
    Ps2xDatPin = dat;
    mPs2x = new PS2X();
    //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
    //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    error = mPs2x->config_gamepad(Ps2xClkPin, Ps2xCmdPin, Ps2xAttPin, Ps2xDatPin, false, false);
    if (error == 1) {
      DEBUG_LOG(DEBUG_LEVEL_ERR, "No controller found, check wiring\n");
    } else if (error == 2) {
      DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller found but not accepting commands\n");
    } else if (error == 3) {
      DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller refusing to enter Pressures mode, may not support it\n");
    } else if (error == 0) {
      DEBUG_LOG(DEBUG_LEVEL_INFO, "Found Controller, configured successful\n");
    }
    Ps2xInit = true;
  }
  return error;
}
int StarterBot::ResetPs2xPin(void)
{
  int error = mPs2x->config_gamepad(Ps2xClkPin, Ps2xCmdPin, Ps2xAttPin, Ps2xDatPin, false, false);
  if (error == 1) {
    DEBUG_LOG(DEBUG_LEVEL_ERR, "No controller found, check wiring\n");
  } else if (error == 2) {
    DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller found but not accepting commands\n");
  } else if (error == 3) {
    DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller refusing to enter Pressures mode, may not support it\n");
  } else if (error == 0) {
    DEBUG_LOG(DEBUG_LEVEL_INFO, "Found Controller, configured successful\n");
  }
  return error;
}
#if ARDUINO > 10609
void StarterBot::SetUltrasonicPin(uint8_t Echo_Pin = EM_ECHO_PIN, uint8_t Trig_Pin = EM_TRIG_PIN, uint8_t Servo_Pin = EM_SERVO_PIN)
#else
void StarterBot::SetUltrasonicPin(uint8_t Echo_Pin, uint8_t Trig_Pin , uint8_t Servo_Pin)
#endif
{
  static bool UltrasonicInit = false;
  if (!UltrasonicInit) {
    EchoPin = Echo_Pin;
    Trig_Pin = Trig_Pin;
    ServoPin = Servo_Pin;
    mUltrasonic = new Ultrasonic(EchoPin, Trig_Pin, ServoPin);
    UltrasonicInit = true;
  }
}
#if ARDUINO > 10609
void StarterBot::SetUltrasonicPin(uint8_t Echo_Pin = EM_ECHO_PIN, uint8_t Trig_Pin = EM_TRIG_PIN)
#else
void StarterBot::SetUltrasonicPin(uint8_t Echo_Pin, uint8_t Trig_Pin)
#endif
{
  static bool UltrasonicInit = false;
  if (!UltrasonicInit) {
    EchoPin = Echo_Pin;
    Trig_Pin = Trig_Pin;
    mUltrasonic = new Ultrasonic(EchoPin, Trig_Pin);
    UltrasonicInit = true;
  }
}

#if ARDUINO > 10609
void StarterBot::SetServoPin(uint8_t Servo_Pin = EM_SERVO_PIN)
#else
void StarterBot::SetServoPin(uint8_t Servo_Pin)
#endif
{
  static bool ServoInit = false;
  if (!ServoInit) {
    ServoPin = Servo_Pin;
    mUltrasonic->ServoPIN(ServoPin);
    ServoInit = true;
  }
}
//front 0 left 1 right 2
#if ARDUINO > 10609
uint16_t StarterBot::GetUltrasonicValue(byte direction = 0)
#else
uint16_t StarterBot::GetUltrasonicValue(byte direction)
#endif
{
  if (direction == 0) {
    return mUltrasonic->GetUltrasonicFrontDistance();
  } else if (direction == 1) {
    return mUltrasonic->GetUltrasonicLeftDistance();
  } else if (direction == 2) {
    return mUltrasonic->GetUltrasonicRightDistance();
  }
}

#if ARDUINO > 10609
void StarterBot::SetPhotoInfraredAvoidancePin(uint8_t L_Avoidance_Pin = EM_IR_AVOIDANCE_LEFT_PIN, uint8_t R_Avoidance_Pin = EM_IR_AVOIDANCE_RIGHT_PIN, uint8_t L_Photo_Pin = EM_PHOTO_LEFT_PIN, uint8_t R_Photo_Pin = EM_PHOTO_RIGHT_PIN)
#else
void StarterBot::SetPhotoInfraredAvoidancePin(uint8_t L_Avoidance_Pin, uint8_t R_Avoidance_Pin, uint8_t L_Photo_Pin, uint8_t R_Photo_Pin)
#endif
{
  static bool InfraredAvoidanceInit = false;
  if (!InfraredAvoidanceInit) {
    LeftIrAvoidance = L_Avoidance_Pin;
    RightIrAvoidance = R_Avoidance_Pin;
    LeftPhotosensitive = L_Photo_Pin;
    RightPhotosensitive = R_Photo_Pin;
    mPhotoIrAvoidance = new InfraredAvoidance(LeftIrAvoidance, RightIrAvoidance, LeftPhotosensitive, RightPhotosensitive);
    InfraredAvoidanceInit = true;
  }
}
#if ARDUINO > 10609
void StarterBot::SetInfraredAvoidancePin(uint8_t L_Avoidance_Pin = EM_IR_AVOIDANCE_LEFT_PIN, uint8_t R_Avoidance_Pin = EM_IR_AVOIDANCE_RIGHT_PIN)
#else
void StarterBot::SetInfraredAvoidancePin(uint8_t L_Avoidance_Pin, uint8_t R_Avoidance_Pin)
#endif
{
  static bool InfraredAvoidanceInit = false;
  if (!InfraredAvoidanceInit) {
    LeftIrAvoidance = L_Avoidance_Pin;
    RightIrAvoidance = R_Avoidance_Pin;
    mPhotoIrAvoidance = new InfraredAvoidance(LeftIrAvoidance, RightIrAvoidance);
    InfraredAvoidanceInit = true;
  }
}

#if ARDUINO > 10609
void StarterBot::SetPhotosensitivePin(uint8_t L_Photo_Pin = EM_PHOTO_LEFT_PIN, uint8_t R_Photo_Pin = EM_PHOTO_RIGHT_PIN)
#else
void StarterBot::SetPhotosensitivePin(uint8_t L_Photo_Pin, uint8_t R_Photo_Pin)
#endif
{
  static bool PhotosensitiveInit = false;
  if (!PhotosensitiveInit) {
    LeftPhotosensitive = L_Photo_Pin;
    RightPhotosensitive = R_Photo_Pin;
    mPhotoIrAvoidance -> PhotosensitivePin(LeftPhotosensitive, RightPhotosensitive);
    PhotosensitiveInit = true;
  }
}

//left 0 right 1
#if ARDUINO > 10609
uint8_t StarterBot::GetInfraredAvoidanceValue(byte direction = 0)
#else
uint8_t StarterBot::GetInfraredAvoidanceValue(byte direction)
#endif
{
  if (direction == 0 ) {
    return mPhotoIrAvoidance->GetLeftInfraredAvoidanceValue();
  } else if (direction == 1 ) {
    return mPhotoIrAvoidance->GetRightInfraredAvoidanceValue();
  } 
}

//left 0 right 1
#if ARDUINO > 10609
int StarterBot::GetPhotosensitive(byte direction = 0)
#else
int StarterBot::GetPhotosensitive(byte direction)
#endif
{
  if (direction == 0 ) {
    return mPhotoIrAvoidance->GetLeftPhotoresistorValue();
  } else if (direction == 1) {
    return mPhotoIrAvoidance->GetRightPhotoresistorValue();
  }
}
#if ARDUINO > 10609
uint8_t StarterBot::GetInfraredTracingValue(byte direction = 0)
#else
uint8_t StarterBot::GetInfraredTracingValue(byte direction)
#endif
{
  if (direction == 0 ) {
    return mInfraredTracing->GetLeftValue();
  } else if (direction == 1) {
    return mInfraredTracing->GetMiddleValue();
  } else if (direction == 2) {
    return mInfraredTracing->GetRightValue();
  }
}

void StarterBot::SendInfraredTracking(void)
{
  byte InfraredTracking_value = mInfraredTracing->GetValue();
  SendData.start_code = PROTOCOL_START_CODE;
  SendData.type = E_STARTER_BOT;
  SendData.addr = 0x01;
  SendData.function = E_INFRARED_TRACKING;
  SendData.data = &InfraredTracking_value;
  SendData.len = 8;
  SendData.end_code = PROTOCOL_END_CODE;
  mProtocolPackage->SendPackage(&SendData, 1);
}

void StarterBot::SendInfraredAvoidanceData(void)
{
  byte InfraredAvoidance_value = (((byte)mPhotoIrAvoidance->GetLeftInfraredAvoidanceValue() & 0xFF) << 1) | ((byte)mPhotoIrAvoidance->GetRightInfraredAvoidanceValue() & 0xFF);
  SendData.start_code = PROTOCOL_START_CODE;
  SendData.type = E_STARTER_BOT;
  SendData.addr = 0x01;
  SendData.function = E_INFRARED_AVOIDANCE;
  SendData.data = &InfraredAvoidance_value;
  SendData.len = 8;
  SendData.end_code = PROTOCOL_END_CODE;
  mProtocolPackage->SendPackage(&SendData, 1);
}

void StarterBot::SendUltrasonicData(void)
{
  union
  {
    float d;
    byte data[4];
  } value;
  value.d = GetUltrasonicValue(FRONT);
  SendData.start_code = 0xAA;
  SendData.type = E_STARTER_BOT;
  SendData.addr = 0x01;
  SendData.function = E_ULTRASONIC;
  SendData.data = value.data;
  SendData.len = 10;
  SendData.end_code = 0x55;
  mProtocolPackage->SendPackage(&SendData, 4);
}

void StarterBot::SendPhotoresistorData(void) {
  byte Photoresistor[2];
  SendData.start_code = PROTOCOL_START_CODE;
  SendData.type = E_STARTER_BOT;
  SendData.addr = 0x01;
  SendData.function = E_PHOTORESISTOR;
  Photoresistor[0] = (mPhotoIrAvoidance->GetLeftPhotoresistorValue() / 10.24);
  Photoresistor[1] = (mPhotoIrAvoidance->GetRightPhotoresistorValue() / 10.24);
  SendData.data = Photoresistor;
  SendData.len = 8;
  SendData.end_code = PROTOCOL_END_CODE;
  mProtocolPackage->SendPackage(&SendData, 2);
}

void StarterBot::SendVersionPackage(void)
{
  char value[5];
  SendData.start_code = PROTOCOL_START_CODE;
  SendData.type = E_STARTER_BOT;
  SendData.addr = 0x01;
  SendData.function = E_VERSION;
  SendData.data = (byte*)value;
  SendData.len = 13;
  SendData.end_code = PROTOCOL_END_CODE;
  mProtocolPackage->SendPackage(&SendData, 5);
}
