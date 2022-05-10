#ifndef __SONAR__
#define __sONAR__
class Sonar{
    public:
        Sonar(int trigPin,int echoPin);
        Sonar(int trigPin,int echoPin,float temp);
        float getDistance();
    private:
        int trigPin;
        int echoPin;
        float vs;
        const float defaultTemp = 20;
};

#endif