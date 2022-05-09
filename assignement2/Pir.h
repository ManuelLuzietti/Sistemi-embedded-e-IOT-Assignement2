#ifndef __PIR__
#define __pIR__
enum State {
    DETECTED, NOTDETECTED
};
class Pir{
    public:
        Pir(int pin);
        void calibrate(int seconds);
        void detect();
        bool isDetected();

    private:
        int pin;
        const int defaultCalibrateTime = 5;
        State status;
};

#endif