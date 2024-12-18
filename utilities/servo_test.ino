void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, 1);

  // ~360 RPM
  for (int i = 0; i < 10000; i++) {
    PORTD = B00001000;
    delayMicroseconds(400);
    PORTD = B00000000;
    delayMicroseconds(400);
  }
  digitalWrite(2, 0);
  for (int i = 0; i < 1000; i++) {
    PORTD = B00001100;
    delayMicroseconds(500);
    PORTD = B00000100;
    delayMicroseconds(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
