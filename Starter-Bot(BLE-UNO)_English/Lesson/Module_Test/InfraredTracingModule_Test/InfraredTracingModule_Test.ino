void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}
void loop() {
  int left, mid, right;
  left = digitalRead(A0);
  mid = digitalRead(A1);
  right = digitalRead(A2);
  Serial.print("right:");
  Serial.print(right);
  Serial.print("   ");
  Serial.print("mid:");
  Serial.print(mid);
  Serial.print("   ");
  Serial.print("left:");
  Serial.print(left);
  Serial.println("   ");
}
