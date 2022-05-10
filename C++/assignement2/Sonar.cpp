#include "Sonar.h"
#include <Arduino.h>

Sonar::Sonar(int trigPin,int echoPin): trigPin(trigPin),echoPin(echoPin){
    this->vs =331.45 + 0.62*this->defaultTemp;
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
}

Sonar::Sonar(int trigPin,int echoPin,float temp): trigPin(trigPin),echoPin(echoPin){
    Sonar(trigPin,echoPin);
    this->vs =331.45 + 0.62*temp;
}

float Sonar::getDistance(){
    digitalWrite(this->trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin,LOW);

    float tUS = pulseIn(echoPin,HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*this->vs;
    return d;

}