//Functions file
void async(){                       //Interrupt function
    isPressed = true;
}
void batteryLevel() {               //Battery monitoring
    keyboard.setBatteryLevel(50);
}

void configuration() {              //Configuration routine
    //ESP_BT.begin("Button accessibility CONFIG");
}

void connection() {                 //Restart BLEKeyboard istance function
    if((millis() - lastRestart)> connection_timeout) {
        keyboard.end();
        Serial.println("Restart BT system");
        delay(50);
        keyboard.begin();
        lastRestart = millis();
    }
}

void blinky(int mode) {
    ledIndex++;                                         //Increment vector pointer
    if(ledIndex > 7)
        ledIndex = 0;
    digitalWrite(led_pin,patterns[mode][ledIndex]);    //Reading current status from patterns table 
}

