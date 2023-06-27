#include <Adafruit_NeoPixel.h>
#ifdef _AVR_
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <ezButton.h>

#define GREEN 2
#define BLUE 1
#define RED 0
#define NUM_LEDS 6


//-------------------- General Params--------------------------
#define MAX_GAME_LENGTH 9
/* Global variables - store the game state */
byte gameSequence[MAX_GAME_LENGTH] = {0};
byte gameIndex = 0;
ezButton mySwitch(32);  // create ezButton object that attach to ESP32 pin GIOP25
int level = 0;
int8_t volume = 0x50;
unsigned long start_level = 7000;
//-------------------- end of General Params--------------------------


//--------------------Screen Display--------------------------
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

// Vertical representation of the numbers

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
//--------------------end of Screen--------------------------


//----------------------NeoPixel----------------------------
Adafruit_NeoPixel pixels(6, 15, NEO_GRB + NEO_KHZ800);
const byte ledPins[] = {15};
//--------------------end of NeoPixel--------------------------


//----------------------Buttons----------------------------
const byte buttonPins[] = {2, 4, 25, 26, 13, 19};
//--------------------end of Buttons--------------------------


//----------------------MP3----------------------------
#include <HardwareSerial.h>
HardwareSerial MP3(2); // Use UART2 for MP3 player communication
static int8_t set_volume[] = {0x7e, 0x03, 0x31, volume, 0xef}; // 7E 03 06 00 EF
static int8_t select_SD_card[] = {0x7e, 0x03, 0X35, 0x01, 0xef}; // 7E 03 35 01 EF
static int8_t play_first_song[] = {0x7e, 0x04, 0x41, 0x00, 0x01, 0xef}; // 7E 04 41 00 01 EF
static int8_t play_second_song[] = {0x7e, 0x04, 0x41, 0x00, 0x02, 0xef}; // 7E 04 41 00 02 EF
static int8_t play_red_song[] = {0x7e, 0x04, 0x41, 0x00, 0x03, 0xef}; // 7E 04 41 00 02 EF
static int8_t play_blue_song[] = {0x7e, 0x04, 0x41, 0x00, 0x04, 0xef}; // 7E 04 41 00 02 EF
static int8_t play_green_song[] = {0x7e, 0x04, 0x41, 0x00, 0x05, 0xef}; // 7E 04 41 00 02 EF
static int8_t play_win_song[] = {0x7e, 0x04, 0x41, 0x00, 0x06, 0xef}; // 7E 04 41 00 02 EF
static int8_t play[] = {0x7e, 0x02, 0x01, 0xef}; // 7E 02 01 EF
static int8_t pauseCmd[] = {0x7e, 0x02, 0x02, 0xef}; // 7E 02 02 EF
#define SPEAKER_PIN 17
//--------------------end of Mp3--------------------------


//--------------------- Game 1----------------------------------
/**
   Lights the given LED and plays a suitable tone
*/
/*void lightLedAndPlayTone(byte ledIndex) {
  digitalWrite(ledPins[ledIndex], HIGH);
  tone(SPEAKER_PIN, gameTones[ledIndex]);
  delay(300);
  digitalWrite(ledPins[ledIndex], LOW);
  noTone(SPEAKER_PIN);
}*/

/**
   plays song
*/
void send_command_to_MP3_player(int8_t command[], int len){
  Serial.print("\nMP3 Command => ");
  for(int i=0;i<len;i++){ MP3.write(command[i]); Serial.print(command[i], HEX); }
  delay(300);
}

/**
   Plays the current sequence of notes that the user has to repeat
*/

bool checkSwitch(){
  int state = mySwitch.getStateRaw();
  if(state==LOW){
    return false;  
  }
  return true;
}

bool playSequence() {
  for (int i = 0; i < gameIndex; i++) {
    byte currentLed = gameSequence[i];
    pixels.setPixelColor(currentLed, pixels.Color(255, 0, 0));
    pixels.show();
    unsigned long startTime = millis();
    unsigned long elapsedTime = 0;
    while (elapsedTime < 300) {
      if(!checkSwitch()){
        return false;
      }
      elapsedTime = millis() - startTime;
    }
    pixels.clear();
    pixels.show();
    delay(300);
  }
  return true;
}

/**
    Waits until the user pressed one of the buttons,
    and returns the index of that button
*/
byte SWITCH_FLAG = 7;

byte readButtons() {
  while (true) {
    if(!checkSwitch()){
        return SWITCH_FLAG;
    }
    for (byte i = 0; i < 6; i++) {
      byte buttonPin = buttonPins[i];
      if (digitalRead(buttonPin) == LOW) {
        delay(300);
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

void printWin(){
  for (int row = 0; row < 8; row++) {
   mx.setColumn(0, row, smile[row]);
   mx.setColumn(1, row, smile[row]);
  }
}

void winner(){
  gameIndex = 0;
  printWin();
  send_command_to_MP3_player(play_win_song, 6);
  delay(2000);
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
const int SIMON_FAIL = 0;
const int SUCCESS = 1;
const int SWITCH = 2;

int checkUserSequence() {
  for (int i = 0; i < gameIndex; i++) {
    if(!checkSwitch()){
       return SWITCH;
    }
    byte expectedButton = gameSequence[i];
    byte actualButton = readButtons();
    if(actualButton == SWITCH_FLAG){
      return SWITCH;
    }
    //lightLedAndPlayTone(actualButton);
    if (expectedButton != actualButton) {
      send_command_to_MP3_player(play_first_song, 6);
      return SIMON_FAIL;
    }
  }
  send_command_to_MP3_player(play_second_song, 6);
  return SUCCESS;
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

//--------------------End Game 1 -------------------------------


//-------------------- Game 2 -------------------------------

byte sequence[6] = {0};
byte presses[6] = {0};

byte readButtons_2() {
  while (true) {
    if(checkSwitch()){
        return SWITCH_FLAG;
    }
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

//--------------------End Game 2 -------------------------------



void setup() {
  mySwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
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


void loop() {
  // read the state of the switch/button:

  mySwitch.loop(); // MUST call the loop() function first
  pixels.clear(); // Set all pixel colors to 'off'
  int state = mySwitch.getState();
  if(gameIndex==0){
      pixels.clear();
      pixels.show();
      delay(1000);
  }
  
  //--------------------------------------- Game 1 ----------------------------------------------
  if (state == HIGH){
    printScore(gameIndex);
    // Add a random color to the end of the sequence
    gameSequence[gameIndex] = random(0, 6);
    if (gameIndex == MAX_GAME_LENGTH) {
      winner();
      return;
    }
    gameIndex++;
    if(!playSequence()){
        gameIndex=0;
        return;
    }
    int res = checkUserSequence();
    if(res == SIMON_FAIL){
      gameOver();
    }else if(res==SWITCH){
      gameIndex=0;
      return;
    }

    delay(300);
  }
  //--------------------------------------- Game 2 ----------------------------------------------
 else{
  printScore(gameIndex);
  if (gameIndex == MAX_GAME_LENGTH) {
      winner();
      return;
    }
  pixels.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    presses[i]=0;
    int color = random(3); // Generate a random number to select a color
    sequence[i] = color;
    if (color == GREEN) {
      pixels.setPixelColor(i, 255, 0, 0);  // Green
      pixels.show();
    } else if (color == BLUE) {
      pixels.setPixelColor(i, 0, 0, 255);  // Blue
      pixels.show();
    } else {
      pixels.setPixelColor(i, 0, 255, 0);  // Red
      pixels.show();
    }
  }
  
  pixels.show(); // Show the updated LED colors
  unsigned long startTime = millis();
  unsigned long elapsedTime = 0;
  
  while (elapsedTime < start_level - level*700) {
      if(checkSwitch()){
        return;
      }
      elapsedTime = millis() - startTime;
  }
  if(start_level - level*1500 >= 1000){
    level++;
  }
  pixels.clear();
  pixels.show(); // Show the updated LED colors

  startTime = millis();
  elapsedTime = 0;
    while (elapsedTime < 2000) {
     if(checkSwitch()){
        level=0;
        return ;
      }
      elapsedTime = millis() - startTime;
    }

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
  if (choosed_color == GREEN) {
      send_command_to_MP3_player(play_green_song, 6);
    } else if (choosed_color == BLUE) {
      send_command_to_MP3_player(play_blue_song, 6);
    } else {
      send_command_to_MP3_player(play_red_song, 6);
    }

  

  while(true){
      byte actualButton = readButtons_2();
      if(actualButton==SWITCH_FLAG){
        gameIndex=0;
        level=0;
        return;
      }
      Serial.print("BUTTON : ");
      Serial.println(actualButton);
      if(sequence[actualButton]!= choosed_color){
        send_command_to_MP3_player(play_first_song, 6);
        gameOver();
        level=0;
        Serial.print("You Lose !");
        return;
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
        send_command_to_MP3_player(play_second_song, 6);
      Serial.print("You win !");
      gameIndex++;
      return;
      }
    }
  }
 
}
