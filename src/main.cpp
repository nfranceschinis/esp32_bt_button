#include <Arduino.h>
#include <Preferences.h>     //For static variables
#include <BleKeyboard.h>     //For normal use
#include <BluetoothSerial.h> //For configuration use

#define button_pin 16 //Button pin
#define led_pin 5     //Button's led pin
#define timeout 1500  //Anti-debounging time
#define led_step 300  //Minimum interval between led change status (used in blinky())
bool isPressed = false;
unsigned long lastPressed = 0;

BleKeyboard keyboard("Button Accessibility", "Nicola Franceschinis", 100); //BLEKeyboard definition --> Format ("Name", "Creator", battery_percentage)
BluetoothSerial ESP_BT;
Preferences statics;

#include <tables.h>                                                    //Bluetooth serial definition (for configuration only)
#include <functions.h>

void setup()  {
  statics.begin("tastiera_esp32", false);
  pinMode(led_pin, OUTPUT);                   //Led pin initialization
  digitalWrite(led_pin, LOW);                 //Led initialization
  pinMode(button_pin, INPUT_PULLUP);          //Button pin initialization
  attachInterrupt(button_pin, async, RISING); //Interrupt initialization
  Serial.begin(115200);                       //Serial debug init
  Serial.println("Starting keyboard system");
  /*if (digitalRead(button_pin))  { //If button is pressed at startup, enter in configuration mode
    configuration();
  }*/
  keyboard.begin(); //BLEKeyboard initialization
  batteryLevel();
}

void loop()
{
  if (keyboard.isConnected())
  { //While no device is connected
    digitalWrite(led_pin, HIGH);
    if (isPressed)
    {
      if ((millis() - lastPressed) > timeout)
      {
        Serial.println("Button pressed!");
        keyboard.write(KEY_BACKSPACE);
        isPressed = false;
        lastPressed = millis();
      }
    }
  }
  digitalWrite(led_pin, LOW);
}