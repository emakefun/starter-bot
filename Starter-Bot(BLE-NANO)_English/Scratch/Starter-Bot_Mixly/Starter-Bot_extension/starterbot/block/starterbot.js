'use strict';

goog.provide('Blockly.Blocks.starterbot');

goog.require('Blockly.Blocks');


Blockly.Blocks.starterbot.HUE = 300;


var STARTERBOT_DIRECTION=[[Blockly.STARTERBOT_DIRECTION_FORWARD, "1"],[Blockly.STARTERBOT_DIRECTION_BACK, "2"],[Blockly.STARTERBOT_DIRECTION_STOP,"5"],[Blockly.STARTERBOT_DIRECTION_TURNLEFT, "3"],[Blockly.STARTERBOT_DIRECTION_TURNRIGHT, "4"]];
var STARTERBOT_CONTROLMODE=[[Blockly.STARTERBOT_CONTROLMODE_BLUETOOTH,"0"],[Blockly.STARTERBOT_CONTROLMODE_REMOTE,"1"],[Blockly.STARTERBOT_CONTROLMODE_IRTRACKING,"2"],[Blockly.STARTERBOT_CONTROLMODE_IRAVOIDANCE,"3"],[Blockly.STARTERBOT_CONTROLMODE_LIGHTFIND,"4"],[Blockly.STARTERBOT_CONTROLMODE_ULTRASONICAVOIDANCE,"5"],[Blockly.STARTERBOT_CONTROLMODE_PS2,"6"],[Blockly.STARTERBOT_CONTROLMODE_NRF24L01,"7"],[Blockly.STARTERBOT_CONTROLMODE_ULTRASONICIRAVOIDANCE,"8"],[Blockly.STARTERBOT_CONTROLMODE_RGB,"10"]];
var STARTERBOT_IRKEY=[["1","12"],["2","13"],["3","14"],["4","15"],["5","16"],["6","17"],["7","18"],["8","19"],["9","20"],["0","9"],["A","0"],["B","1"],["C","2"],["D","3"],["+","5"],["-","11"],[Blockly.STARTERBOT_IRKEY_UP,"4"],[Blockly.STARTERBOT_IRKEY_DOWN,"10"],["OK","7"],[Blockly.STARTERBOT_IRKEY_LEFT,"6"],[Blockly.STARTERBOT_IRKEY_RIGHT,"8"]];
var STARTERBOT_ULTRASONICDIRECTION=[[Blockly.STARTERBOT_ULTRASONICDIRECTION_FRONT,"0"],[Blockly.STARTERBOT_ULTRASONICDIRECTION_LEFT,"1"],[Blockly.STARTERBOT_ULTRASONICDIRECTION_RIGHT,"2"]];
var STARTERBOT_IRAVOIDANCEDIRECTION=[[Blockly.STARTERBOT_IRAVOIDANCEDIRECTION_LEFT,"0"],[Blockly.STARTERBOT_IRAVOIDANCEDIRECTION_RIGHT,"1"]]; 
var STARTERBOT_PS2KEY=[[Blockly.STARTERBOT_PS2KEY_UP,"0x0010"],[Blockly.STARTERBOT_PS2KEY_DOWN,"0x0040"],[Blockly.STARTERBOT_PS2KEY_LEFT,"0x0080"],[Blockly.STARTERBOT_PS2KEY_RIGHT,"0x0020"],["×","0x4000"],["○","0x2000"],["△","0x1000"],["□","0x8000"]];
var STARTERBOT_TRACKINGVALUE=[[Blockly.STARTERBOT_TRACKINGVALUE_BLACK,"0"],[Blockly.STARTERBOT_TRACKINGVALUE_WHITE,"7"],[Blockly.STARTERBOT_TRACKINGVALUE_CENTER,"5"],[Blockly.STARTERBOT_TRACKINGVALUE_RIGHT1,"6"],[Blockly.STARTERBOT_TRACKINGVALUE_RIGHT2,"4"],[Blockly.STARTERBOT_TRACKINGVALUE_LEFT1,"3"],[Blockly.STARTERBOT_TRACKINGVALUE_LEFT2,"1"]];
var STARTERBOT_BLUETOOTHKEY=[[Blockly.STARTERBOT_BLUETOOTHKEY_UP,"0"],[Blockly.STARTERBOT_BLUETOOTHKEY_DOWN,"1"],[Blockly.STARTERBOT_BLUETOOTHKEY_LEFT,"2"],[Blockly.STARTERBOT_BLUETOOTHKEY_RIGHT,"3"],[Blockly.STARTERBOT_BLUETOOTHKEY_SPEEDUP,"4"],[Blockly.STARTERBOT_BLUETOOTHKEY_SPEEDDOWN,"5"]];
var STARTERBOT_PHOTOSENSITIVE=[[Blockly.STARTERBOT_PHOTOSENSITIVE_LEFT,"0"],[Blockly.STARTERBOT_PHOTOSENSITIVE_RIGHT,"1"]];
var STARTERBOT_RGBNUMBER=[[Blockly.STARTERBOT_RGBNUMBER_ALL,"0"],[Blockly.STARTERBOT_RGBNUMBER_LEFT,"1"],[Blockly.STARTERBOT_RGBNUMBER_RIGHT,"2"]];
var STARTERBOT_RGBCOLOR=[[Blockly.STARTERBOT_RGBCOLOR_RED,"0xFF0000"],[Blockly.STARTERBOT_RGBCOLOR_GREEN,"0x00FF00"],[Blockly.STARTERBOT_RGBCOLOR_BLUE,"0x0000FF"],[Blockly.STARTERBOT_RGBCOLOR_YELLOW,"0xFFFF00"],[Blockly.STARTERBOT_RGBCOLOR_PURPLE,"0xFF00FF"],[Blockly.STARTERBOT_RGBCOLOR_WHITE,"0xFFFFFF"],[Blockly.STARTERBOT_RGBCOLOR_OFF,"0x000000"]];

//第0个图形块的样式,Hummerbot初始化
Blockly.Blocks.eb_setup = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_SETUP)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_starterbot.png", 45, 38))
	this.setPreviousStatement(false,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};

//第一个图形块的样式,小车行驶方向下拉（下拉没有value），速度（输入,有value）
Blockly.Blocks.eb_move = {
  init: function() {
	    this.setColour(Blockly.Blocks.starterbot.HUE);
        this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_MOVE)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_starterbot.png", 45, 38))
        .appendField(new Blockly.FieldDropdown(STARTERBOT_DIRECTION), "Direction")
        .appendField(Blockly.STARTERBOT_SPEED);
	    this.appendValueInput("Speed", Number)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	    this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
        this.setTooltip('');
  }
};
//第二个图形块的样式,小车操控模式下拉（下拉没有value）
Blockly.Blocks.eb_mode = {
	init:function(){
	    this.setColour(Blockly.Blocks.starterbot.HUE);
		this.appendDummyInput("")
			.appendField(Blockly.STARTERBOT_MODE)
		    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_starterbot.png", 45, 38))
			.appendField(new Blockly.FieldDropdown(STARTERBOT_CONTROLMODE),"Mode")
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
		}
};
//第三个图形块的样式,舵机引脚（输入，有value），舵机校正角度（输入，有value）
Blockly.Blocks.eb_servo = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_SERVO)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_servo.png", 45, 38))
    this.appendValueInput("ServoPin", Number)
        .appendField(Blockly.STARTERBOT_SERVOPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("ServoDegree", Number)
        .appendField(Blockly.STARTERBOT_SERVODEGREE)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
Blockly.Blocks.eb_servoangle = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_SERVO)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_servo.png", 45, 38))
    this.appendValueInput("ServoAngle", Number)
        .appendField(Blockly.STARTERBOT_SERVOANGLE)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第四个图形块的样式,四个电机引脚（输入，有value）
Blockly.Blocks.eb_motor = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_MOTORPIN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_motor.png", 45, 38))
    this.appendValueInput("LeftNegativeValue", Number)
        .appendField(Blockly.STARTERBOT_LEFTNEGATIVEPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("LeftPositiveValue", Number)
        .appendField(Blockly.STARTERBOT_LEFTPOSITIVEPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendValueInput("RightNegativeValue", Number)
        .appendField(Blockly.STARTERBOT_RIGHTNEGATIVEPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("RightPositiveValue", Number)
        .appendField(Blockly.STARTERBOT_RIGHTPOSITIVEPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第五个图形块的样式,转弯角度（输入，有value），速度（输入，有value）
Blockly.Blocks.eb_turn = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_TURN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_starterbot.png", 45, 38))
    this.appendValueInput("TurnAngle", Number)
        .appendField(Blockly.STARTERBOT_TURNANGLE)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("Speed", Number)
        .appendField(Blockly.STARTERBOT_SPEED)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第六个图形块的样式,加速
Blockly.Blocks.eb_speedup = {
 init:function(){
	 this.setColour(Blockly.Blocks.starterbot.HUE);
	 this.appendDummyInput("")        
		 .appendField(new Blockly.FieldImage("../../media/starterbot/eb_starterbot.png", 45, 38))
		 .appendField(Blockly.STARTERBOT_SPEEDUP)
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
 }
};
//第七个图形块的样式,加速
Blockly.Blocks.eb_speeddown = {
 init:function(){
	 this.setColour(Blockly.Blocks.starterbot.HUE);
	 this.appendDummyInput("")        
		 .appendField(new Blockly.FieldImage("../../media/starterbot/eb_starterbot.png", 45, 38))
		 .appendField(Blockly.STARTERBOT_SPEEDDOWN)
	this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
 }
};
Blockly.Blocks.eb_getcurrentspeed = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_GETCURRENTSPEED)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_starterbot.png", 45, 38))		
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第八个图形块的样式 红外接收初始化
Blockly.Blocks.eb_irReceive = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_IRRECEIVEPIN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_irremote.png", 45, 38))
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//红外遥控按键被按下（下拉，返回boolean）
Blockly.Blocks.eb_irKeyPressed = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_IRKEYPRESSED)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_irremote.png", 45, 38))
		
    this.setOutput(true, Boolean);
    this.setTooltip('');
  }
};
//第九个图形块的样式 红外遥控按键（下拉，返回boolean）
Blockly.Blocks.eb_irKeyPress = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_IRKEYPRESS)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_irremote.png", 45, 38))
		.appendField(new Blockly.FieldDropdown(STARTERBOT_IRKEY), "Irkey")
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十个图形块的样式 超声波模块两个引脚,rgb引脚（输入 有value）
Blockly.Blocks.eb_ultrasonicpin = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_ULTRASONICPIN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_ultrasonic.png", 45, 38))
    this.appendValueInput("SingPin", Number)
        .appendField(Blockly.STARTERBOT_SING)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("RGBPin", Number)
        .appendField(Blockly.STARTERBOT_RGB)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第十一个图形块的样式(setOutput) 超声波测距（下拉，前，左，右）
Blockly.Blocks.eb_readUltrasonicDistance = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_READULTRASONICDISTANCE)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_ultrasonic.png", 45, 38))
		.appendField(new Blockly.FieldDropdown(STARTERBOT_ULTRASONICDIRECTION), "UltrasonicDirection")
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十二个图形块的样式 红外避障模块两个引脚(输入，有value)    field的name不确定使NUM待检测
Blockly.Blocks.eb_irAvoidance = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_IRAVOIDANCEPIN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_lightfind.png", 45, 38))
    this.appendValueInput("LeftPin", Number)
        .appendField(Blockly.STARTERBOT_LEFTPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("RightPin", Number)
        .appendField(Blockly.STARTERBOT_RIGHTPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//追光模块
Blockly.Blocks.eb_photosensitivePin = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_PHOTOSENSITIVEPIN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_lightfind.png", 45, 38))
    this.appendValueInput("LeftPin", Number)
        .appendField(Blockly.STARTERBOT_LEFTPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("RightPin", Number)
        .appendField(Blockly.STARTERBOT_RIGHTPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//左右光弱度模块
Blockly.Blocks.eb_getPhotosensitive = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_GETPHOTOSENSITIVE)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_lightfind.png", 45, 38))
		.appendField(new Blockly.FieldDropdown(STARTERBOT_PHOTOSENSITIVE), "Photosensitive")
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十三个图形块的样式 红外避障测距（下拉，左，右）
Blockly.Blocks.eb_readIrAvoidanceDistance = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_READIRAVOIDANCEDISTANCE)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_lightfind.png", 45, 38))
		.appendField(new Blockly.FieldDropdown(STARTERBOT_IRAVOIDANCEDIRECTION), "IrAvoidanceDirection")
    this.setOutput(true, Number);
    this.setTooltip('');
  }
};
//第十四个图形块的样式 PS2模块四个引脚(输入，有value)
Blockly.Blocks.eb_PS2Pin = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_PS2PIN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_ps2.png", 45, 38))
    this.appendValueInput("CLKPin", Number)
        .appendField(Blockly.STARTERBOT_CLKPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("CMDPin", Number)
        .appendField(Blockly.STARTERBOT_CMDPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendValueInput("ATTPin", Number)
        .appendField(Blockly.STARTERBOT_ATTPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("DATPin", Number)
        .appendField(Blockly.STARTERBOT_DATPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
}; 
//第十五个图形块的样式 定义PS2摇杆震动值
Blockly.Blocks.eb_varPS2vibrate = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_VARPS2VIBRATE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_ps2.png", 45, 38))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//第十六个图形块的样式 设置PS2摇杆震动值
Blockly.Blocks.eb_setPS2vibrate = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_SETPS2VIBRATE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_ps2.png", 45, 38))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//第十七个图形块的样式 PS2键被按下（返回boolean）
Blockly.Blocks.eb_PS2KeyPressed = {
  init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_PS2KEYPRESSED)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_ps2.png", 45, 38))
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第十八个图形块的样式 PS2键被按下（下拉）
Blockly.Blocks.eb_WhichPS2KeyPressed = {
  init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_WHICHPS2KEYPRESSED)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_ps2.png", 45, 38))
	    .appendField(new Blockly.FieldDropdown(STARTERBOT_PS2KEY), "PS2Key")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第十九个图形块的样式 红外循迹模块三个引脚(输入，有value)
Blockly.Blocks.eb_IrTrackingPin = {
  init: function() {
    this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
        .appendField(Blockly.STARTERBOT_IRTRACKINGPIN)
		.appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
    this.appendValueInput("IrTrackingLeftPin", Number)
        .appendField(Blockly.STARTERBOT_IRTRACKINGLEFTPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.appendValueInput("IrTrackingMidPin", Number)
        .appendField(Blockly.STARTERBOT_IRTRACKINGMIDPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
	this.appendValueInput("IrTrackingRightPin", Number)
        .appendField(Blockly.STARTERBOT_IRTRACKINGRIGHTPIN)
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
  }
};
//第二十个图形块的样式 读取循迹状态（下拉）
Blockly.Blocks.eb_readTrackingValue = {
  init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_READTRACKINGVALUE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
	    //.appendField(new Blockly.FieldDropdown(STARTERBOT_TRACKINGVALUE), "TrackingValue")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
Blockly.Blocks.eb_readTrackingValues = {
  init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_READTRACKINGVALUE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
	    .appendField(new Blockly.FieldDropdown(STARTERBOT_TRACKINGVALUE), "TrackingValue")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第二十一个图形块的样式 定义一个保存上一次循迹状态的变量
Blockly.Blocks.eb_setByteOld = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_SETBYTEOLD)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//第二十二个图形块的样式 当前循迹状态（下拉）
Blockly.Blocks.eb_recentTrackingValue = {
  init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);  
	this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_RECENTTRACKINGVALUE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
	    .appendField(new Blockly.FieldDropdown(STARTERBOT_TRACKINGVALUE), "TrackingValue")
	this.setOutput(true, Boolean);
	this.setTooltip('');
  }
};
//第二十三个图形块的样式 清除上一次循迹状态
Blockly.Blocks.eb_cleanLastTrackingValue = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_CLEANLASTTRACKINGVALUE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//第二十四个图形块的样式 当前循迹状态不是全白
Blockly.Blocks.eb_recentTrackingValueIsNotWhite = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_RECENTTRACKINGVALUEISNOTWHITE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
	this.setOutput(true,Boolean);  
	this.setTooltip('');
 }
};
//第二十五个图形块的样式 重置上一次循迹状态
Blockly.Blocks.eb_resetLastTrackingValue = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_RESETLASTTRACKINGVALUE)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_irtracking.png", 45, 38))
		.appendField(new Blockly.FieldDropdown(STARTERBOT_TRACKINGVALUE), "TrackingValue")
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//第二十六个图形块的样式 接收蓝牙数据
Blockly.Blocks.eb_receiveBluetoothData = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_RECEIVEBLUETOOTHDATA)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_bluetooth.png", 45, 38))
	this.setPreviousStatement(true,null);
    this.setNextStatement(true,null);   
	this.setTooltip('');
 }
};
//第二十七个图形块的样式 接收到了蓝牙数据
Blockly.Blocks.eb_receivedBluetoothData = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_RECEIVEDBLUETOOTHDATA)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_bluetooth.png", 45, 38))
	this.setOutput(true,Boolean);  
	this.setTooltip('');
 }
};
//第二十八个图形块的样式 蓝牙操控键按下（下拉）
Blockly.Blocks.eb_bluetoothKeyPressed = {
 init:function(){
	this.setColour(Blockly.Blocks.starterbot.HUE);
    this.appendDummyInput("")
	    .appendField(Blockly.STARTERBOT_BLUETOOTHKEYPRESSED)
	    .appendField(new Blockly.FieldImage("../../media/starterbot/eb_bluetooth.png", 45, 38))
		.appendField(new Blockly.FieldDropdown(STARTERBOT_BLUETOOTHKEY), "BluetoothKey")
	this.setOutput(true,Boolean);  
	this.setTooltip('');
 }
};