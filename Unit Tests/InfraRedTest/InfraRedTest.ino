int ir=13;
int led=14;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(112500);

}

void loop() {
  int irvalue = digitalRead(ir);
  if(irvalue==LOW){
    Serial.print("LOW");
    digitalWrite(led,HIGH);
  }
  else{
    Serial.print("HIGH");
    digitalWrite(led,LOW);
  }
  delay(100);

}
