#include "Servo.h"
#include <Arduino.h>

Servo::Servo(int pin){
    this->pin = pin;
    this->servo = new ServoTimer2();
}

void Servo::on(){
    this->servo->attach(this->pin);
}
void Servo::off(){
    this->servo->detach();
}


void Servo::setPosition(int angle){
    int ms = map(angle,0,180,this->minPulseWidth,this->maxPulseWidth);
    this->servo->write(ms);
}
