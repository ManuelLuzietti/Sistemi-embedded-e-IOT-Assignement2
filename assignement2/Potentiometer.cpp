#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
    this->pin = pin;
}

int Potentiometer::getValue(){
    return analogRead(this->pin);
};