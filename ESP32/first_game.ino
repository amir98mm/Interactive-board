

#include <Adafruit_NeoPixel.h>
#ifdef _AVR_
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

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

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
Adafruit_NeoPixel pixels(6, 15, NEO_GRB + NEO_KHZ800);

#include <HardwareSerial.h>
HardwareSerial MP3(2); // Use UART2 for MP3 player communication
static int8_t set_volume[] = {0x7e, 0x03, 0x31, 0x08, 0xef}; // 7E 03 06 00 EF
static int8_t select_SD_card[] = {0x7e, 0x03, 0X35, 0x01, 0xef}; // 7E 03 35 01 EF
static int8_t play_first_song[] = {0x7e, 0x04, 0x41, 0x00, 0x01, 0xef}; // 7E 04 41 00 01 EF
static int8_t play_second_song[] = {0x7e, 0x04, 0x41, 0x00, 0x02, 0xef}; // 7E 04 41 00 02 EF
static int8_t play[] = {0x7e, 0x02, 0x01, 0xef}; // 7E 02 01 EF
static int8_t pauseCmd[] = {0x7e, 0x02, 0x02, 0xef}; // 7E 02 02 EF

/* Constants - define pin numbers for LEDs,
   buttons and speaker, and also the game tones: */
const byte ledPins[] = {15};
const byte buttonPins[] = {2, 4, 25, 26, 19, 13};
#define SPEAKER_PIN 17

#define MAX_GAME_LENGTH 100

const int gameTones[] = { NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5};

/* Global variables - store the game state */
byte gameSequence[MAX_GAME_LENGTH] = {0};
byte gameIndex = 0;

/**
   Set up the ESP32 board and initialize Serial communication
*/
void setup() {
  mx.begin();               // Initialize MD_MAX72XX
  mx.control(MD_MAX72XX::INTENSITY, 4);  // Set brightness (0-15)
  mx.clear();               // Clear the display
  Serial.begin(9600);
  MP3.begin(9600, SERIAL_8N1, 17, 16);
  // Select the SD Card.
  send_command_to_MP3_player(select_SD_card, 5);
  send_command_to_MP3_player(set_volume, 5);
  pixels.begin();
  for (byte i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(SPEAKER_PIN, OUTPUT);
  // The following line primes the random number generator.
  // It assumes pin A0 is floating (disconnected):
  randomSeed(analogRead(A0));
}

/**
   Lights the given LED and plays a suitable tone
*/
void lightLedAndPlayTone(byte ledIndex) {
  digitalWrite(ledPins[ledIndex], HIGH);
  tone(SPEAKER_PIN, gameTones[ledIndex]);
  delay(300);
  digitalWrite(ledPins[ledIndex], LOW);
  noTone(SPEAKER_PIN);
}

void send_command_to_MP3_player(int8_t command[], int len){
  Serial.print("\nMP3 Command => ");
  for(int i=0;i<len;i++){ MP3.write(command[i]); Serial.print(command[i], HEX); }
  delay(300);
}

/**
   Plays the current sequence of notes that the user has to repeat
*/
void playSequence() {
  for (int i = 0; i < gameIndex; i++) {
    byte currentLed = gameSequence[i];
    //lightLedAndPlayTone(currentLed);
    
    pixels.setPixelColor(currentLed, pixels.Color(255,0 , 0));
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(300);
    pixels.clear(); // Set all pixel colors to 'off'
    pixels.show(); 
    delay(300);
    tone(SPEAKER_PIN, gameTones[currentLed]);
    delay(300);
  }
}

/**
    Waits until the user pressed one of the buttons,
    and returns the index of that button
*/
byte readButtons() {
  while (true) {
    for (byte i = 0; i < 6; i++) {
      byte buttonPin = buttonPins[i];
      if (digitalRead(buttonPin) == LOW) {
        delay(500);
        Serial.print("===>");
        Serial.print(i);
        return i;
      }
    }
    delay(1);
  }
}

void printLose(){
  for (int row = 0; row < 8; row++) {
   mx.setColumn(0, row, sad[row]);
   mx.setColumn(1, row, sad[row]);
  }
}

/**
  Play the game over sequence, and report the game score
*/
void gameOver() {
  Serial.print("Game over! your score: ");
  Serial.println(gameIndex - 1);
  gameIndex = 0;
  printLose();
  delay(2000);
}

/**
   Get the user's input and compare it with the expected sequence.
*/
bool checkUserSequence() {
  for (int i = 0; i < gameIndex; i++) {
    byte expectedButton = gameSequence[i];
    byte actualButton = readButtons();
    lightLedAndPlayTone(actualButton);
    if (expectedButton != actualButton) {
      send_command_to_MP3_player(play_second_song, 6);
      return false;
    }
  }
  send_command_to_MP3_player(play_first_song, 6);
  return true;
}

/**
   Plays a hooray sound whenever the user finishes a level
*/
void playLevelUpSound() {
  tone(SPEAKER_PIN, NOTE_E4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_G4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_E5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_C5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_D5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_G5);
  delay(150);
  noTone(SPEAKER_PIN);
}

/**
   The main game loop
*/
void printScore(int gameIndex){
  int first=gameIndex%10;
  int sec=gameIndex/10;
  for (int row = 0; row < 8; row++) {
   mx.setColumn(0, row, nums[sec][row]);
   mx.setColumn(1, row, nums[first][row]);
  }
}

void loop() {
  printScore(gameIndex);
  // Add a random color to the end of the sequence
  gameSequence[gameIndex] = random(0, 6);
  gameIndex++;
  if (gameIndex >= MAX_GAME_LENGTH) {
    gameIndex = MAX_GAME_LENGTH - 1;
  }

  playSequence();
  if (!checkUserSequence()) {
    gameOver();
  }

  delay(300);

  if (gameIndex > 0) {
//    playLevelUpSound();
//    delay(300);
  }
}
