//Functions file
void async(){                       //Interrupt function
    isPressed = true;
}

int getSerialNumber(void) {         //Function for getting serial number saved on SPIFFS
    int serialNumber = 0;
    return serialNumber;
}

byte ButtonSetup(bool mode, byte command) {     //Function for read(0) / write(1) command to send 
    if(!mode) { //Read data
        //byte memory_read = command;
        return '\n';
    }
    else {      //write data
        byte memory_read = 0x30;
        return memory_read;
    }
} 

void blinky(int mode) {             //Function for manage button led UI
    if((millis() - lastLedStat) > led_step) {
        ledIndex++;                                         //Increment vector pointer
        if(ledIndex > 7)
            ledIndex = 0;
        digitalWrite(led_pin,patterns[mode][ledIndex]);    //Reading current status from patterns table
        lastLedStat = millis();
    } 
}

void batteryLevel() {               //Battery monitoring
    keyboard.setBatteryLevel(50);
}

void configuration() {              //Configuration routine
    Serial.println("Entering configuration mode...");
    
    byte buffer[buffer_lenght];     //For temporary stocking
    int pointer = 0;              //For pointing buffer vector

    while(!wasConnected) {
        blinky(1);                  //UI mode: Configuration
        message received = {0x00, 0x00, 0x00};
        while(Serial.available()) {         //Receving command
            byte packet = Serial.read();
            if((char)packet == '\n') {      //If end-packet is sent
                memcpy(&received, buffer, pointer);     //Move buffer into structure
                pointer = 0;
            }
            else{
                buffer[pointer] = packet;
                pointer++;
            }
        }
        switch (received.command) {         //Packets elaboration
            case 0x0F:      //Data request
                switch (received.message) {
                    case 0x01:      //Return Serial Number
                        Serial.print("Serial number:    ");
                        Serial.println(getSerialNumber());
                    break;
                    case 0x02:      //Return current button setup
                        Serial.print("Current button setup:     ");
                        Serial.println(ButtonSetup(0, 0));
                    break;
                }
                break;
            case 0xF0:      //Data modification
                switch (received.message) {
                    case 0x01:      //Set Serial Number
                        Serial.print("Set Serial Number:    ");
                        Serial.println(received.payload);
                    break;
                    case 0x02:      //Set button command
                        Serial.print("Set button command:     ");
                        Serial.println(received.payload);
                    break;
                }
                break;
            case 0xFF:      //Exit from configuration mode
                Serial.println("Exiting configuration mode");
                wasConnected = true;
                break;
        }
        /*char c = 0x00;
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
        } */
    }
}