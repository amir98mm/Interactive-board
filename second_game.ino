#include <Adafruit_NeoPixel.h>

#define LED_PIN 15
#define NUM_LEDS 4
#define LED_TYPE NEO_GRB + NEO_KHZ800
#define GREEN 0
#define BLUE 1
#define RED 2

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, LED_TYPE);
byte sequence[6] = {0};
byte presses[6] = {0};
const byte buttonPins[] = {2, 4, 25, 26};


void setup() {
  Serial.begin(9600);
  leds.begin();
  leds.show(); // Initialize all LEDs to an off state
  for (byte i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

byte readButtons() {
  while (true) {
    for (byte i = 0; i < 4; i++) {
      byte buttonPin = buttonPins[i];
      if (digitalRead(buttonPin) == LOW) {
        return i;
      }
    }
    delay(1);
  }
}

void loop() {
  leds.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    presses[i]=0;
    int color = random(3); // Generate a random number to select a color
    sequence[i] = color;
    if (color == GREEN) {
      leds.setPixelColor(i, 0, 255, 0);  // Green
      leds.show();
    } else if (color == BLUE) {
      leds.setPixelColor(i, 0, 0, 255);  // Blue
      leds.show();
    } else {
      leds.setPixelColor(i, 255, 0, 0);  // Red
      leds.show();
    }
  }
  
  leds.show(); // Show the updated LED colors

  //delay(2000);
  //for (int i = 0; i < NUM_LEDS; i++) {
     //leds.setPixelColor(i, 0, 0, 0);  // Red
     //leds.show();
  //}
  delay(2000);
  leds.clear();
  leds.show(); // Show the updated LED colors

  delay(2000);

  for(int i = 0; i < NUM_LEDS; i++){
    Serial.print(sequence[i]);
  }

  int choosed_color = random(3);
  bool not_contains = true;
  while(not_contains){
    for(int i=0; i<NUM_LEDS; i++){
      if(choosed_color == sequence[i]){
        not_contains = false;
      }
    }
    if(!not_contains){
       break;
    }
    choosed_color = random(3);
  }
  Serial.print(choosed_color);
  

  while(true){
      byte actualButton = readButtons();
      

      if(sequence[actualButton]!= choosed_color){
        Serial.print("You Lose !");
        break;
      }
      else{
        presses[actualButton]=1;
      }
      int flag=0;
      for(int i = 0; i < NUM_LEDS; i++){
        if(sequence[i]==choosed_color && presses[i]==0){
         
          flag=1;
          break;
        }
      }
      if(flag==0) {
      Serial.print("You win !");
      break;
      }
  }

  
}
  
  
