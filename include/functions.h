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
    digitalWrite(led_pin, LOW);                         //Led status initialization
    unsigned long interval = 0;                         //Interval memory (for waiting routine)
    for(int index=0;index < 8;index++){
        digitalWrite(led_pin,patterns[mode][index]);    //Reading current status from patterns table 
        while(millis() - interval < led_step){}         //Waiting routine between next status reading
        interval = millis();
    }
}

