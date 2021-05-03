//Functions file
int getSerialNumber(void) {         //Function for getting serial number saved on SPIFFS
    int serialNumber = 0;
    return serialNumber;
}

void async(){                       //Interrupt function
    isPressed = true;
}
void batteryLevel() {               //Battery monitoring
    keyboard.setBatteryLevel(50);
}

void configuration() {              //Configuration routine
    Serial.println("Entering configuration mode...");
    while(!wasConnected) {
        /*while(keyboard_config.connected()){
            while(keyboard_config.available()){
                Serial.print(keyboard_config.read());
            }
        }*/
        char c = 0x00;

        if(keyboard_config.available())
            c = keyboard_config.read();
        switch (c)  {
            case 'A':           //Return serial number
                keyboard_config.print("Serial Number:    ");
                keyboard_config.println(getSerialNumber());
                c = 0x00;
                break;
            case 'Q':           //
                keyboard_config.println("Exiting configuration mode");
                wasConnected = true;
                c = 0x00;
                break;
        } 
    }
}

void blinky(int mode) {
    if((millis() - lastLedStat) > led_step) {
        ledIndex++;                                         //Increment vector pointer
        if(ledIndex > 7)
            ledIndex = 0;
        digitalWrite(led_pin,patterns[mode][ledIndex]);    //Reading current status from patterns table
        lastLedStat = millis();
    } 
}