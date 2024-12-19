#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include "morse.c"
#include "mqtt.c"
#include "led.c"
#define led 0
#define btn 1


int main(int argc, char* argv[]){
    wiringPiSetup();
    pinMode(LED_PIN, OUTPUT);  // Definition of GPIO as an output

    MQTTBegin ();
    MQTTSubscribe (TOPIC);
    while(1) {
        while (digitalRead(btn)==1);
        MQTTPublish (TOPIC, "Message à messager");
        while(digitalRead(btn)==0);
    };
    MQTTDisconnect();

 // make sure an argument was trasnfered
    if (argc > 1) {
        // turn a text into morse
        std::string morseCode = EnglishToMorse(argv[1]);
        std::cout << "Code Morse: " << morseCode << std::endl;
        
        // send morse to the led
        MorseToLed(morseCode.c_str());
    } else {
        std::cout << "Aucun texte à convertir en morse." << std::endl;
    }

    return 0;
}
}

    return 0;
}


