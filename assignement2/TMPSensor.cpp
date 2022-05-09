#include "TMPSensor.h"
#include <Arduino.h>

TMPSensor::TMPSensor(int pin): pin(pin){
    pinMode(pin,INPUT);
}

double TMPSensor::getValue(){
    int value = analogRead(this->pin);
    double value_in_mV =  4.8876 * value;
    //double value_in_C = value_in_mV * 0.1;
    double value_in_C = (value_in_mV -500 )*0.1;
    return value_in_C;
}
