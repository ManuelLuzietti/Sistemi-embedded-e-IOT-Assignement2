#ifndef __TMPSENSOR__
#define __TMPSENSOR__
class TMPSensor{
    public:
        TMPSensor(int pin);
        double getValue();
    private:
        int pin;
};

#endif