#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  ---  left
#define IN3_PIN 5   // PWMA
#define IN4_PIN 9   // DIRA  ---  right

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop()
{
  int left, mid, right;
  left = digitalRead(A0);
  mid = digitalRead(A1);
  right = digitalRead(A2);
  if ((right == 1) && (mid == 0) && (left == 1)) 
  {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 130);
    analogWrite(IN3_PIN, 130);
    analogWrite(IN4_PIN, 0);
  }
  else  if ((right == 0) && (mid == 1) && (left == 1)) //righ 1
  {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 130);
    analogWrite(IN3_PIN, 20);
    analogWrite(IN4_PIN, 0);
  }
  else  if ((right == 0) && (mid == 0) && (left == 1)) //righ 2
  {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 120);
    analogWrite(IN3_PIN, 20);
    analogWrite(IN4_PIN, 0);
  }
  else  if ((right == 1) && (mid == 1) && (left == 0))//left 1
  {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 20);
    analogWrite(IN3_PIN, 130);
    analogWrite(IN4_PIN, 0);
  }
   else  if ((right == 1) && (mid == 0) && (left == 0))//left 2
  {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 20);
    analogWrite(IN3_PIN, 130);
    analogWrite(IN4_PIN, 0);
  }
  else if ((right == 0) && (mid == 0) && (left == 0))
  {
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 0);
    analogWrite(IN3_PIN, 0);
    analogWrite(IN4_PIN, 0);
  }
}
