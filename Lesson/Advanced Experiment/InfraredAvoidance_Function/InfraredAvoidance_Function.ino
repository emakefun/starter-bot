#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  ---  left
#define IN3_PIN 5   // PWMA
#define IN4_PIN 9   // DIRA  ---  right
const int leftPin = 12;
const int rightPin = A5;
byte LeftValue,RightValue;
void setup()
{
  Serial.begin(9600);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  delay(1000);
}

void loop()
{
  LeftValue = digitalRead(leftPin);
  RightValue = digitalRead(rightPin);
  if (LeftValue == 1 && RightValue == 1)
  {
    analogWrite(IN1_PIN, 0); 
    analogWrite(IN2_PIN, 130);
    analogWrite(IN3_PIN, 130);
    analogWrite(IN4_PIN, 0); 
    Serial.print(LeftValue);
    Serial.print("   ");
    Serial.print(RightValue);
    Serial.print("   ");
    Serial.println("go");//********************************************//forward
    } 
    else if (LeftValue ==1 && RightValue ==0) 
    {
        analogWrite(IN1_PIN, 180); 
        analogWrite(IN2_PIN, 0);
        analogWrite(IN3_PIN, 0);
        analogWrite(IN4_PIN, 180); 
        delay(200); 
        analogWrite(IN1_PIN, 180);
        analogWrite(IN2_PIN, 0); //the speed value of motorA is 180
        analogWrite(IN3_PIN, 180);
        analogWrite(IN4_PIN, 0); //the speed value of motorB is 180
        Serial.print(LeftValue);
        Serial.print("   ");
        Serial.print(RightValue);
        Serial.print("   ");
        Serial.println("Turning left");
        delay(300);
        analogWrite(IN1_PIN, 0);
        analogWrite(IN2_PIN, 0);
        analogWrite(IN3_PIN, 0);
        analogWrite(IN4_PIN, 0);
        delay(1000); //********************************************//Turning left
    } else if (LeftValue ==0 && RightValue ==0) {
       analogWrite(IN1_PIN, 180); 
        analogWrite(IN2_PIN, 0);
        analogWrite(IN3_PIN, 0);
        analogWrite(IN4_PIN, 180); 
        delay(200);
        analogWrite(IN1_PIN, 0);
        analogWrite(IN2_PIN, 255); //the speed value of motorA is 255
        analogWrite(IN3_PIN, 0);
        analogWrite(IN4_PIN, 255); //the speed value of motorB is 255
        Serial.print(LeftValue);
        Serial.print("   ");
        Serial.print(RightValue);
        Serial.print("   ");
        Serial.println("Turning around");
        delay(500);
        analogWrite(IN1_PIN, 0);
        analogWrite(IN2_PIN, 0);
        analogWrite(IN3_PIN, 0);
        analogWrite(IN4_PIN, 0);
        delay(1000); //********************************************//Turning around
    } else if (LeftValue ==0 && RightValue == 1) {
       analogWrite(IN1_PIN, 180); 
        analogWrite(IN2_PIN, 0);
        analogWrite(IN3_PIN, 0);
        analogWrite(IN4_PIN, 180); 
        delay(200);
        analogWrite(IN1_PIN, 0); //the speed value of motorA is val
        analogWrite(IN2_PIN, 180);
        analogWrite(IN3_PIN, 0); //the speed value of motorA is val
        analogWrite(IN4_PIN, 180);
        Serial.print(LeftValue);
        Serial.print("   ");
        Serial.print(RightValue);
        Serial.print("   ");
        Serial.println("Turning right");
        delay(300);
        analogWrite(IN1_PIN, 0);
        analogWrite(IN2_PIN, 0);
        analogWrite(IN3_PIN, 0);
        analogWrite(IN4_PIN, 0);
        delay(1000); //********************************************//Turning right
    }
}
