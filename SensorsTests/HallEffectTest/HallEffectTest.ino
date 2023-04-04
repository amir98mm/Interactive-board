const int hallPin = 17;

void setup() {
  pinMode(hallPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  int hallValue = digitalRead(hallPin);
  Serial.println(hallValue);
  delay(1000);
}
