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

void blinky(int mode) {
    ledIndex++;                                         //Increment vector pointer
    if(ledIndex > 7)
        ledIndex = 0;
    digitalWrite(led_pin,patterns[mode][ledIndex]);    //Reading current status from patterns table 
}

