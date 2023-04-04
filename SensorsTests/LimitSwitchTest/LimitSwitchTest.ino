int switchPin = 17; // the digital pin connected to the switch
int switchState = 0; // variable to store the state of the switch

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  switchState =  digitalRead(switchPin);
  if(switchState){
    Serial.println("ON");
  }
  else{
    Serial.println("OFF");
  }
  
  delay(100);
}
