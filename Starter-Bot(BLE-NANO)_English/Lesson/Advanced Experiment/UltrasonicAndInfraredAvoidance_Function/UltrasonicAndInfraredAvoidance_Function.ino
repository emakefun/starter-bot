#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  left
#define INPUT3_PIN 5   // PWMA
#define INPUT4_PIN 9   // DIRA  ---  right
const int leftPin = 12;
const int rightPin = A5;
const int TrigPin = 2;
const int EchoPin = 3;
int ServoPin = 13;
float da, dl, dr;
byte LeftValue, RightValue;

void SetServoDegree(int Angle)
{
  for (int i = 0; i < 80; i++)
  {
    float pulsewidth = (Angle * 11) + 350;
    digitalWrite(ServoPin, HIGH);   //Set the servo interface level to high
    delayMicroseconds(pulsewidth);  //The number of microseconds of the delay pulse width value
    digitalWrite(ServoPin, LOW);    //Set the servo interface level to low
    delayMicroseconds(20000 - pulsewidth);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(ServoPin, OUTPUT);
  pinMode(INPUT1_PIN, OUTPUT);
  pinMode(INPUT2_PIN, OUTPUT);
  pinMode(INPUT3_PIN, OUTPUT);
  pinMode(INPUT4_PIN, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  SetServoDegree(90);
  delay(1000);
}

void loop()
{
  LeftValue = digitalRead(leftPin);
  RightValue = digitalRead(rightPin);
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH );
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  da = pulseIn(EchoPin, HIGH) / 58.0;
  if ((LeftValue == 1) && (RightValue == 1) && (da > 15))
  {
    SetServoDegree(90);
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 130);
    analogWrite(INPUT3_PIN, 130);
    analogWrite(INPUT4_PIN, 0);
  }
  else if ((LeftValue == 1) && (RightValue == 1) && (da < 15))
  {
    analogWrite(INPUT1_PIN, 180);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 180);
    delay(200);
     analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 0);
    SetServoDegree(180);
    delay(1000);
    analogWrite(TrigPin, 0); //Send a short pulse to TrigPin
    delayMicroseconds(2);
    analogWrite(TrigPin, 255);
    delayMicroseconds(10);
    analogWrite(TrigPin, 0);
    dl = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted to cm

    SetServoDegree(20);
    delay(1000);
    analogWrite(TrigPin, 0);
    delayMicroseconds(2);
    analogWrite(TrigPin, 255);
    delayMicroseconds(10);
    analogWrite(TrigPin, 0);
    dr = pulseIn(EchoPin, HIGH) / 58.0;

    SetServoDegree(90);

    if ((dl > 15) && (dr > 15))
    {
      if (dl > dr)
      {
        analogWrite(INPUT1_PIN, 150);
        analogWrite(INPUT2_PIN, 0);
        analogWrite(INPUT3_PIN, 150);
        analogWrite(INPUT4_PIN, 0);
        Serial.println("Turning left1");
        delay(150);
      }
      else
      {
        analogWrite(INPUT1_PIN, 0);
        analogWrite(INPUT2_PIN, 150);
        analogWrite(INPUT3_PIN, 0);
        analogWrite(INPUT4_PIN, 150);
        Serial.println("Turning right1");
        delay(150);
      }
    }
    else if ((dl >= 15) || (dr > 15))
    {
      if (dl > 15)
      {
        analogWrite(INPUT1_PIN, 150);
        analogWrite(INPUT2_PIN, LOW);
        analogWrite(INPUT3_PIN, 150);
        analogWrite(INPUT4_PIN, LOW);
        Serial.println("Turning left2");
        delay(150);
      }
      if (dr > 15)
      {
        analogWrite(INPUT1_PIN, 0);
        analogWrite(INPUT2_PIN, 150);
        analogWrite(INPUT3_PIN, 0);
        analogWrite(INPUT4_PIN, 150);
        Serial.println("Turning right2");
        delay(150);
      }
    }
    else
    {
      analogWrite(INPUT1_PIN, 150);
      analogWrite(INPUT2_PIN, 0);
      analogWrite(INPUT3_PIN, 150);
      analogWrite(INPUT4_PIN, 0);
      Serial.println("Turning around");
      delay(200);
    }
  }
  else if ((LeftValue == 1) && (RightValue == 0) && (da > 15) )
  {
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 20);
    analogWrite(INPUT3_PIN, 250);
    analogWrite(INPUT4_PIN, 0);
    delay(300);
  }
  else if ((LeftValue == 1) && (RightValue == 0) && (da < 15) )
  {
    analogWrite(INPUT1_PIN, 180);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 180);
    delay(200);
    analogWrite(INPUT1_PIN, 180);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 180);
    analogWrite(INPUT4_PIN, 0);
    delay(300);
  }
   else if ((LeftValue == 0) && (RightValue == 1) && (da > 15) )
  {
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 250);
    analogWrite(INPUT3_PIN, 20);
    analogWrite(INPUT4_PIN, 0);
    delay(300);
  }
  else if ((LeftValue == 0) && (RightValue == 1) && (da < 15) )
  {
    analogWrite(INPUT1_PIN, 180);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 180);
    delay(200);
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 180);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 180);
    delay(300);
  }
  else if ((LeftValue == 0) && (RightValue == 0) && (da > 15) )
  {
    analogWrite(INPUT1_PIN, 180);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 180);
    delay(300);
  }
  else if ((LeftValue == 0) && (RightValue == 0) && (da < 15) )
  {
    analogWrite(INPUT1_PIN, 180);
    analogWrite(INPUT2_PIN, 0);
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 180);
    delay(400);
    analogWrite(INPUT1_PIN, 0);
    analogWrite(INPUT2_PIN, 255); //the speed value of motorA is 255
    analogWrite(INPUT3_PIN, 0);
    analogWrite(INPUT4_PIN, 255); //the speed value of motorB is 255
    delay(200);
  }
}
