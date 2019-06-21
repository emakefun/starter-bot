'use strict';

goog.provide('Blockly.Arduino.starterbot');

goog.require('Blockly.Arduino');

//将第0个图形块转化为C语言 StarterBot初始化
Blockly.Arduino.eb_setup = function() {
 Blockly.Arduino.definitions_['define_Arduino'] = '#include<Arduino.h>'; 
 //Blockly.Arduino.definitions_['define_wire'] = '#include<wire.h>'; 
 Blockly.Arduino.definitions_['define_SoftwareSerial'] = '#include<SoftwareSerial.h>'; 
 Blockly.Arduino.definitions_['define_ProtocolParser'] = '#include<ProtocolParser.h>'; 
 Blockly.Arduino.definitions_['define_BluetoothHandle'] = '#include<BluetoothHandle.h>'; 
 Blockly.Arduino.definitions_['define_KeyMap'] = '#include<KeyMap.h>'; 
 Blockly.Arduino.definitions_['define_debug'] = '#include<debug.h>'; 
 Blockly.Arduino.definitions_['define_StarterBot'] = '#include<StarterBot.h>';
 Blockly.Arduino.definitions_['object'] = 'ProtocolParser *mProtocol = new ProtocolParser();\nStarterBot Ebot(mProtocol, EM_IN1_PIN, EM_IN2_PIN, EM_IN3_PIN, EM_IN4_PIN);\nbyte Ps2xStatus, Ps2xType;'
 Blockly.Arduino.setups_['setup_eb_setup'] ='\t'+'Ebot.init();\n'
                                            +'\t'+'Ebot.SetSpeed(0);\n'
											+'\t'+'Ebot.SetControlMode((E_SMARTCAR_CONTROL_MODE)(0));\n'
											+'\t'+'Ps2xType = Ebot.mPs2x->readType();\n'
 var code = '';
 return code;
};
//将第一个图形块转化为C语言 小车行驶方向下拉（下拉没有value），速度（输入,有value）
Blockly.Arduino.eb_move = function() {
 var dropdown_Direction = this.getFieldValue('Direction');
 var value_Speed = Blockly.Arduino.valueToCode(this,'Speed',Blockly.Arduino.ORDER_ATOMIC);
 var code = 'Ebot.SetSpeed('+value_Speed+');\n'
 			+'Ebot.Move('+dropdown_Direction+');\n';
return code;
};
//将第二个图形块转化为C语言 小车操控模式下拉（下拉没有value）
Blockly.Arduino.eb_mode = function(){
 var dropdown_Mode = this.getFieldValue('Mode');
 Blockly.Arduino.setups_['setup_eb_mode'] ='\t'+'Ebot.SetControlMode('+'(E_SMARTCAR_CONTROL_MODE)'+dropdown_Mode+');\n'
 var code = ''
 return code;
};
//将第三个图形块转化为C语言 舵机引脚（输入，有value），舵机校正角度（输入，有value）
Blockly.Arduino.eb_servo = function(){
 var value_servo_pin = Blockly.Arduino.valueToCode(this, 'ServoPin', Blockly.Arduino.ORDER_ATOMIC);
 var value_servo_degree = Blockly.Arduino.valueToCode(this, 'ServoDegree', Blockly.Arduino.ORDER_ATOMIC);
	     Blockly.Arduino.setups_['setup_eb_servo'] = '\t'+'Ebot.SetServoPin('+value_servo_pin+');\n'
								   +'\t'+'Ebot.mUltrasonic->SetServoBaseDegree('+value_servo_degree+');\n'
								   +'\t'+'Ebot.mUltrasonic->SetServoDegree(90);\n'
 var code = '';
 return code;
};
Blockly.Arduino.eb_servoangle = function(){
 
 var value_servo_angle = Blockly.Arduino.valueToCode(this, 'ServoAngle', Blockly.Arduino.ORDER_ATOMIC);
	    
 var code = '	Ebot.mUltrasonic->SetServoDegree('+value_servo_angle+');';
 return code;
};
//将第四个图形块转化为C语言 四个电机引脚（输入，有value）
Blockly.Arduino.eb_motor = function(){
 var value_LeftNegativeValue = Blockly.Arduino.valueToCode(this,'LeftNegativeValue',Blockly.Arduino.ORDER_ATOMIC);	
 var value_LeftPositiveValue = Blockly.Arduino.valueToCode(this,'LeftPositiveValue',Blockly.Arduino.ORDER_ATOMIC);	
 var value_RightNegativeValue = Blockly.Arduino.valueToCode(this,'RightNegativeValue',Blockly.Arduino.ORDER_ATOMIC);	
 var value_RightPositiveValue = Blockly.Arduino.valueToCode(this,'RightPositiveValue',Blockly.Arduino.ORDER_ATOMIC);	
Blockly.Arduino.setups_['setup_eb_motor'] ='\t'+'Ebot.SetMotorPin('
									+value_LeftNegativeValue+','
									+value_LeftPositiveValue+','
									+value_RightNegativeValue+','
									+value_RightPositiveValue+');\n';
 var code = '';
 return code;
};
//将第五个图形块转化为C语言 转弯角度（输入，有value），速度（输入，有value）
Blockly.Arduino.eb_turn = function(){
 var value_TurnAngle = Blockly.Arduino.valueToCode(this,'TurnAngle',Blockly.Arduino.ORDER_ATOMIC);
 var value_Speed = Blockly.Arduino.valueToCode(this,'Speed',Blockly.Arduino.ORDER_ATOMIC);
 var code = 'Ebot.SetSpeed('+value_Speed+');\n'
		  +'Ebot.Drive('+value_TurnAngle+');\n';
 return code;
};
//将第六个图形块转化为C语言 加速
Blockly.Arduino.eb_speedup = function(){
 var code = 'Ebot.SpeedUp(5);\n';
 return code;
};
//将第七个图形块转化为C语言 减速
Blockly.Arduino.eb_speeddown = function(){
 var code = 'Ebot.SpeedDown(5);\n';
 return code;
};
Blockly.Arduino.eb_getcurrentspeed = function(){
 var code = 'Ebot.GetSpeed()';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; //当code为表达式时用此返回方式
};
//将第八个图形块转化为C语言 红外接收初始化
Blockly.Arduino.eb_irReceive = function(){
 Blockly.Arduino.setups_['setup_eb_irReceive'] ='\t'+'Ebot.IrInit();\n'
 var code = '';
 return code;
};
Blockly.Arduino.eb_irKeyPressed = function(){
 Blockly.Arduino.definitions_['define_irremote'] = 'byte irKeyCode;\n'; 
 var code = 'irKeyCode = Ebot.mIrRecv->getCode()';
 return [code, Blockly.Arduino.ORDER_ATOMIC];
};
//将第九个图形块转化为C语言 红外遥控按键（下拉，返回boolean）
Blockly.Arduino.eb_irKeyPress = function(){
 var dropdown_Irkey = this.getFieldValue('Irkey');
 var code = '(E_IR_KEYCODE)Ebot.mIrRecv->getIrKey(Ebot.mIrRecv->getCode()) == '+dropdown_Irkey+'';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; //当code为表达式时用此返回方式
};
//将第十个图形块转化为C语言 超声波模块两个引脚,rgb引脚（输入 有value）
Blockly.Arduino.eb_ultrasonicpin = function(){
 var value_SingPin = Blockly.Arduino.valueToCode(this,'SingPin',Blockly.Arduino.ORDER_ATOMIC);
 var value_RGBPin = Blockly.Arduino.valueToCode(this,'RGBPin',Blockly.Arduino.ORDER_ATOMIC);
 Blockly.Arduino.setups_['setup_eb_ultrasonicpin'] ='\t'+'Ebot.SetUltrasonicpin('+value_SingPin+','+value_RGBPin+');\n'
 var code = '';
 return code;
};
//将第十一个图形块转化为C语言 超声波测距（下拉，前，左，右）
Blockly.Arduino.eb_readUltrasonicDistance = function(){
 var dropdown_UltrasonicDirection=this.getFieldValue('UltrasonicDirection');
 var code = 'Ebot.GetUltrasonicValue('+dropdown_UltrasonicDirection+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第十二个图形块转化为C语言 红外避障模块两个引脚(输入，有value)    field的name不确定使NUM待检测
Blockly.Arduino.eb_irAvoidance = function(){
 var value_LeftPin = Blockly.Arduino.valueToCode(this,'LeftPin',Blockly.Arduino.ORDER_ATOMIC);
 var value_RightPin = Blockly.Arduino.valueToCode(this,'RightPin',Blockly.Arduino.ORDER_ATOMIC);
 Blockly.Arduino.setups_['setup_eb_irAvoidance'] ='\t'+'Ebot.SetInfraredAvoidancePin('+value_LeftPin+','+value_RightPin+');\n'
 var code = '';
 return code;
};
//追光模块转化为C语言
Blockly.Arduino.eb_photosensitivePin = function(){
 var value_LeftPin = Blockly.Arduino.valueToCode(this,'LeftPin',Blockly.Arduino.ORDER_ATOMIC);
 var value_RightPin = Blockly.Arduino.valueToCode(this,'RightPin',Blockly.Arduino.ORDER_ATOMIC);
 Blockly.Arduino.setups_['eb_photosensitivePin'] ='\t'+'Ebot.SetPhotosensitivePin('+value_LeftPin+','+value_RightPin+');\n'
 var code = '';
 return code;
};
//光弱度值
Blockly.Arduino.eb_getPhotosensitive = function(){
 var dropdown_Photosensitive = this.getFieldValue('Photosensitive');
 var code = 'Ebot.GetPhotosensitive('+dropdown_Photosensitive+')/10';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; //当code为表达式时用此返回方式
};
//将第十三个图形块转化为C语言 红外避障测距（下拉，左，右）
Blockly.Arduino.eb_readIrAvoidanceDistance = function(){
 var dropdown_IrAvoidanceDirection = this.getFieldValue('IrAvoidanceDirection');
 var code = 'Ebot.GetInfraredAvoidanceValue('+dropdown_IrAvoidanceDirection+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第十四个图形块转化为C语言 PS2模块四个引脚(输入，有value)
Blockly.Arduino.eb_PS2Pin = function(){
 var value_CLKPin = Blockly.Arduino.valueToCode(this,'CLKPin',Blockly.Arduino.ORDER_ATOMIC); 
 var value_CMDPin = Blockly.Arduino.valueToCode(this,'CMDPin',Blockly.Arduino.ORDER_ATOMIC); 
 var value_ATTPin = Blockly.Arduino.valueToCode(this,'ATTPin',Blockly.Arduino.ORDER_ATOMIC); 
 var value_DATPin = Blockly.Arduino.valueToCode(this,'DATPin',Blockly.Arduino.ORDER_ATOMIC); 
 Blockly.Arduino.setups_['setup_eb_PS2Pin'] ='\t'+'Ebot.SetPs2xPin('
									+value_CLKPin+','
									+value_CMDPin+','
									+value_ATTPin+','
									+value_DATPin+');\n'																												
 var code = '';
 return code;
};
//将第十五个图形块转化为C语言 定义PS2摇杆震动值
Blockly.Arduino.eb_varPS2vibrate = function(){
 var code = 'static int vibrate = 0;\nbyte PSS_X = 0,PSS_Y = 0;\nEbot.mPs2x->read_gamepad(false, vibrate);\n';
 return code;
};
//将第十六个图形块转化为C语言 设置PS2摇杆震动值
Blockly.Arduino.eb_setPS2vibrate = function(){
 var code = 'vibrate = Ebot.mPs2x->Analog(PSAB_CROSS);\n';
 return code;
};
//将第十七个图形块转化为C语言 PS2键被按下（返回boolean）
Blockly.Arduino.eb_PS2KeyPressed = function(){
var code = 'Ebot.mPs2x->ButtonDataByte()';
return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第十八个图形块转化为C语言 PS2键被按下（下拉）
Blockly.Arduino.eb_WhichPS2KeyPressed = function(){
 var dropdown_PS2Key = this.getFieldValue('PS2Key');
 var code = 'Ebot.mPs2x->Button('+dropdown_PS2Key+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第十九个图形块转化为C语言 红外循迹模块三个引脚(输入，有value)
Blockly.Arduino.eb_IrTrackingPin = function(){
 var value_IrTrackingLeftPin = Blockly.Arduino.valueToCode(this,'IrTrackingLeftPin',Blockly.Arduino.ORDER_ATOMIC); 
 var value_IrTrackingMidPin = Blockly.Arduino.valueToCode(this,'IrTrackingMidPin',Blockly.Arduino.ORDER_ATOMIC); 
 var value_IrTrackingRightPin = Blockly.Arduino.valueToCode(this,'IrTrackingRightPin',Blockly.Arduino.ORDER_ATOMIC); 
  Blockly.Arduino.setups_['setup_eb_SetInfraredTracingPin'] ='\t'+'Ebot.SetInfraredTracingPin('+value_IrTrackingLeftPin+','+value_IrTrackingMidPin+','+value_IrTrackingRightPin+');\n';
 var code = '';
 return code;
};
//将第二十个图形块转化为C语言 读取循迹状态（下拉）
Blockly.Arduino.eb_readTrackingValue = function(){
 var dropdown_TrackingValue = this.getFieldValue('TrackingValue');
 var code = 'Ebot.mInfraredTracing->GetValue()';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
Blockly.Arduino.eb_readTrackingValues = function(){
 var dropdown_TrackingValue = this.getFieldValue('TrackingValue');
 var code = dropdown_TrackingValue;
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第二十一个图形块转化为C语言 定义一个保存上一次循迹状态的变量
Blockly.Arduino.eb_setByteOld = function(){
 var code = 'static byte old;\n';
 return code;
};
//将第二十二个图形块转化为C语言 当前循迹状态（下拉）
Blockly.Arduino.eb_recentTrackingValue = function(){
 var dropdown_TrackingValue = this.getFieldValue('TrackingValue');
 var code = 'old=='+dropdown_TrackingValue+'';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第二十三个图形块转化为C语言 清除上一次循迹状态
Blockly.Arduino.eb_cleanLastTrackingValue = function(){
 var code = 'old=0;\n'+'break;\n';
 return code;
};
//将第二十四个图形块转化为C语言 当前循迹状态不是全白
Blockly.Arduino.eb_recentTrackingValueIsNotWhite = function(){
var code = '(Ebot.mInfraredTracing->getValue()==IT_ALL_BLACK)||(Ebot.mInfraredTracing->getValue()==IT_RIGHT1)||(Ebot.mInfraredTracing->getValue()==IT_RIGHT2)||(Ebot.mInfraredTracing->getValue()==IT_LEFT1)||(Ebot.mInfraredTracing->getValue()==IT_LEFT2)||(Ebot.mInfraredTracing->getValue()==IT_CENTER)'; 
return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第二十五个图形块转化为C语言 重置上一次循迹状态
Blockly.Arduino.eb_resetLastTrackingValue = function(){
 var dropdown_TrackingValue = this.getFieldValue('TrackingValue');
 var code = 'old='+dropdown_TrackingValue+';\n';
 return code;
};
//将第二十六个图形块转化为C语言 接收蓝牙数据
Blockly.Arduino.eb_receiveBluetoothData = function(){
 var code = 'mProtocol->RecevData();\n';
 return code;
};
//将第二十七个图形块转化为C语言 接收到了蓝牙数据
Blockly.Arduino.eb_receivedBluetoothData = function(){
 var code = 'mProtocol->ParserPackage()';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第二十八个图形块转化为C语言 蓝牙操控键按下
Blockly.Arduino.eb_bluetoothKeyPressed = function(){
 var dropdown_BluetoothKey = this.getFieldValue('BluetoothKey');
 var code = 'mProtocol->GetBluetoothButton('+dropdown_BluetoothKey+')'
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};