
//here is the screen
#include <MD_MAX72xx.h>
#include <SPI.h>

// Constants for MAX7219 configuration
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES  2
#define WRAPAROUND_MODE MD_MAX72XX::ON

#define CLK_PIN   18  // or SCK
#define DATA_PIN  23  // or MOSI
#define CS_PIN    5  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Vertical representation of the number "5"

const uint8_t verticalNumber0[] = {
0x00,0x18,0x24,0x24,0x24,0x24,0x18,0x00};

const uint8_t verticalNumber1[] = {
0x10,0x18,0x14,0x10,0x10,0x10,0x38,0x00};


const uint8_t verticalNumber2[] = {
0x3C,0x20,0x20,0x3C,0x04,0x04,0x3C,0x00
};

const uint8_t verticalNumber3[] = {
0x3C,0x20,0x20,0x3C,0x20,0x20,0x3C,0x00};

const uint8_t verticalNumber4[] = {
0x24,0x24,0x24,0x3C,0x20,0x20,0x20,0x00};

const uint8_t verticalNumber5[] = {
  B00111100,
  B00000100,
  B00000100,
  B00111100,
  B00100000,
  B00100000,
  B00111100,
  B00000000

};

const uint8_t verticalNumber6[] = {
0x3C,0x04,0x04,0x3C,0x24,0x24,0x3C,0x00};

const uint8_t verticalNumber7[] = {
0x3C,0x24,0x20,0x20,0x20,0x20,0x20,0x00};

const uint8_t verticalNumber8[] = {
0x3C,0x24,0x24,0x3C,0x24,0x24,0x3C,0x00};

const uint8_t verticalNumber9[] = {
0x3C,0x24,0x24,0x3C,0x20,0x20,0x3C,0x00};


const uint8_t smile[] = {
0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C
};

const uint8_t* nums[10]={verticalNumber0,verticalNumber1,verticalNumber2,verticalNumber3,verticalNumber4,verticalNumber5,verticalNumber6,verticalNumber7,verticalNumber8,verticalNumber9};

const uint8_t sad[] = {
0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C
};
//end of screen code
//-----------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>

#define LED_PIN 15
#define NUM_LEDS 6
#define LED_TYPE NEO_GRB + NEO_KHZ800
#define GREEN 2
#define BLUE 1
#define RED 0

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, LED_TYPE);
byte sequence[6] = {0};
byte presses[6] = {0};
const byte buttonPins[] = {2, 4, 25, 26, 19, 13};
//-----------------------------------------------------------------------

byte gameIndex = 0;

void setup() {
  mx.begin();               // Initialize MD_MAX72XX
  mx.control(MD_MAX72XX::INTENSITY, 4);  // Set brightness (0-15)
  mx.clear();               // Clear the display
  Serial.begin(9600);
  leds.begin();
  leds.show(); // Initialize all LEDs to an off state
  for (byte i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void gameOver() {
  Serial.print("Game over! your score: ");
  Serial.println(gameIndex);
  gameIndex = 0;
  printLose();
  delay(2000);
}

void printLose(){
  for (int row = 0; row < 8; row++) {
   mx.setColumn(0, row, sad[row]);
   mx.setColumn(1, row, sad[row]);
  }
}

void printScore(int gameIndex){
  int first=gameIndex%10;
  int sec=gameIndex/10;
  for (int row = 0; row < 8; row++) {
   mx.setColumn(0, row, nums[sec][row]);
   mx.setColumn(1, row, nums[first][row]);
  }
}

byte readButtons() {
  while (true) {
    for (byte i = 0; i < 6; i++) {
      byte buttonPin = buttonPins[i];
      if (digitalRead(buttonPin) == LOW) {
        return i;
      }
    }
    delay(1);
  }
}

void loop() {
  printScore(gameIndex);
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
  delay(6000);
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
        gameOver();
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
      gameIndex++;
      break;
      }
  }

  
}
  
  
