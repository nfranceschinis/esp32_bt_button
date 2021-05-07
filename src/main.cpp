#include <Arduino.h>
#include <Preferences.h>     //For static variables
#include <BleKeyboard.h>     //For normal use
#include <BluetoothSerial.h> //For configuration use

#define button_pin 2 //Button pin 5
#define led_pin 15     //Button's led pin LED_BUILTIN
#define timeout 200  //Anti-debounging time
#define connection_timeout 3000   //Timeout before restart BLEKeyboard in order to be seen
#define led_step 1000  //Minimum interval between led change status (used in blinky())
#define buffer_lenght 10   //Size of buffer for Serial comunication

bool isPressed = false;
bool wasConnected = false;      //Flag for one-time setup for 
unsigned long lastPressed = 0;
unsigned long lastRestart = 0;
unsigned long lastLedStat = 0;
int ledIndex = 0;

BleKeyboard keyboard("Cjosul button", "CjosuLab", 100); //BLEKeyboard definition --> Format ("Name", "Creator", battery_percentage)
BluetoothSerial keyboard_config;
Preferences statics;

#include <tables.h>                                                    //Bluetooth serial definition (for configuration only)
#include <functions.h>

void setup()  {
  pinMode(led_pin, OUTPUT);                   //Led pin initialization
  digitalWrite(led_pin, LOW);                 //Led initialization
  pinMode(button_pin, INPUT_PULLUP);          //Button pin initialization
  Serial.begin(115200);                       //Serial debug init
  Serial.println("Starting keyboard system");
  /*if (!digitalRead(button_pin))  { //If button is pressed at startup, enter in configuration mode
    keyboard_config.begin("Cjosul_config");
    configuration();
    keyboard_config.end();
  }*/
  attachInterrupt(button_pin, async, RISING); //Interrupt initialization
  keyboard.begin(); //BLEKeyboard initialization
  batteryLevel();
}

void loop()
{
  if (keyboard.isConnected()) { //While device is connected
    digitalWrite(led_pin, HIGH);
    if (isPressed)  {
      if ((millis() - lastPressed) > timeout) { //If interrupt was not caused by a debounce signal 
        Serial.println("Button pressed!");      //debug
        keyboard.write(KEY_MEDIA_NEXT_TRACK);
        keyboard.releaseAll();
        isPressed = false;
        lastPressed = millis();
      }
      isPressed = false;
    }
  }
  else{
    blinky(0);          //UI mode: not connected
  }
}