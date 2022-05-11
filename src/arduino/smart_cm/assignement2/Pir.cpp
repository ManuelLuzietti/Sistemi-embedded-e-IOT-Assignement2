#include "Pir.h"
#include <Arduino.h>

Pir::Pir(int pin){
    this->pin = pin;
    pinMode(pin,INPUT);
    calibrate(this->defaultCalibrateTime);
    this->status = NOTDETECTED;
}

void Pir::calibrate(int seconds){
    for(int i=0; i<seconds; i++){
        delay(1000);
    }
}

void Pir::detect(){
    int currentSignal = digitalRead(this->pin);
    State currentStatus;
    if(currentSignal){
        currentStatus = DETECTED;
    } else {
        currentStatus = NOTDETECTED;
    }
    if(currentStatus != this->status){
        this->status = currentStatus;
    }
}

bool Pir::isDetected(){
    return this->status == DETECTED;
}
