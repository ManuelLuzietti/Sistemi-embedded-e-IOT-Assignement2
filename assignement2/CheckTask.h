#ifndef __CHECKTASK__
#define __CHECKTASK___
#include "Task.h"
#include "TMPSensor.h"
#include "MachineModelSingleton.h"
#include "MachineModel.h"
#include "Servo.h"
#define TCHECK 180000
#define TMAX 40
#define TMIN 18

class CheckTask : public Task
{
    enum CheckStates
    {
        Off,
        On,
        Assistance
    } checkState;
    int elapsed;
    TMPSensor* tmpSensor;
    Servo* servo;
    Display *display;
    int angle;
    int delta;
    bool to180;
    bool to0;
    bool motorTest;
    bool tempTest;

    void testMotor()
    {
        if (!to180)
        {
            if (angle < 180)
            {
                angle += delta;
                if (angle >= 180)
                {
                    angle = 180;
                    to180 = true;
                }
                servo->setPosition(angle);
            }
        }
        if (to180 && !to0)
        {
            if (angle > 0)
            {
                angle -= 10;
                if (angle <= 0)
                {
                    angle = 0;
                    to0 = true;
                }
                servo->setPosition(angle);
            }
        }
        if (to180 && to0)
        {
            motorTest = true;
        }
    }

    void checkTmp()
    {
        double temp = tmpSensor->getValue();
        Serial.println(String("temp ")+ temp);
        if (temp > TMAX || temp < TMIN)
        {
            checkState = Assistance;
            tempTest = false;
            display->print("Assistance required");
        } 
    }
    void initVars()
    {
        angle = 0;
        delta = 10;
        to180 = false;
        to0 = false;
        motorTest = false;
        tempTest = true;
    }

public:
    CheckTask(int tmpPin, int servoPin)
    {
        tmpSensor = new TMPSensor(tmpPin);
        servo = new Servo(servoPin);
    }

    void init(int period)
    {
        display = new Display(0x27, 16, 2);
        Task::init(period);
        checkState = Off;
        elapsed = 0;
        initVars();
    }

    void tick()
    {
        switch (checkState)
        {
        case Off:
            Serial.println("check task off");
            elapsed += Task::myPeriod;
            if (elapsed > TCHECK  && MachineModelSingleton::getInstance()->getMachineState() == Idle )
            {
                checkState = On;
                servo->on();
                display->print("Check test");
                MachineModelSingleton::getInstance()->setAssistanceState();
            }
            break;
        case On:

            Serial.println("check on");

            checkTmp();
            testMotor();
            if (motorTest && tempTest && checkState == On)
            {
                checkState = Off;
                initVars();
                servo->off();
                elapsed = 0;
            }
            break;
        case Assistance:
            Serial.println("check assistance");
            //cambiare stato per uscire da assistance
            if(MachineModelSingleton::getInstance()->getMachineState() == Idle ){
                checkState = Off;
                initVars();
                elapsed = 0;
                servo->off();
            }
            break;
        }
    }
};

#endif 