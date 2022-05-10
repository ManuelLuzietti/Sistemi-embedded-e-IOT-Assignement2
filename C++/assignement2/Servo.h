#ifndef __SERVO__
#define __SERVO__
#include <ServoTimer2.h>
class Servo{
    public:
        Servo(int pin);
        void on();
        void off();
        void setPosition(int angle);

    private:
        ServoTimer2* servo;
        int pin;
        const int maxPulseWidth = 2250;
        const int minPulseWidth = 750;
};

#endif