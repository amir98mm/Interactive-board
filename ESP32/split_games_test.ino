#define BUTTON_PIN 21 // GIOP21 pin connected to button
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef _AVR_
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <ezButton.h>

ezButton mySwitch(25);  // create ezButton object that attach to ESP32 pin GIOP25
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 3 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
// Variables will change:
int lastState = HIGH; // the previous state from the input pin
int currentState;     // the current reading from the input pin

int switchPin = 16; // the digital pin connected to the switch
int switchState = 0; // variable to store the state of the switch

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(_AVR_ATtiny85_) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  // initialize the pushbutton pin as an pull-up input
  pinMode(BUTTON_PIN, INPUT_PULLUP);




    mySwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
  Serial.begin(115200);
}


void loop() {
  // read the state of the switch/button:

  mySwitch.loop(); // MUST call the loop() function first
    pixels.clear(); // Set all pixel colors to 'off'
    int state = mySwitch.getState();

    
  if (state == HIGH){
    
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.
    
    delay(DELAYVAL);

  }

  }
 else{
    
      currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH)
    Serial.println("The state changed from LOW to HIGH");

  // save the last state
  lastState = currentState;
  }


  delay(DELAYVAL);


  
}

//////////
/*
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



/////////////////////
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef _AVR_
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 3 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(_AVR_ATtiny85_) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}





#include <ezButton.h>

ezButton mySwitch(25);  // create ezButton object that attach to ESP32 pin GIOP25

void setup() {
  Serial.begin(9600);
  mySwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  mySwitch.loop(); // MUST call the loop() function first

  if (mySwitch.isPressed())
    Serial.println("The switch: OFF -> ON");

  if (mySwitch.isReleased())
    Serial.println("The switch: ON -> OFF");

  int state = mySwitch.getState();
  if (state == HIGH)
    Serial.println("The switch: OFF");
  else
    Serial.println("The switch: ON");
}



*/
