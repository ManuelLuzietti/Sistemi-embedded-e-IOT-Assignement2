#ifndef __CHECKTASK__
#define __CHECKTASK___
#include "Task.h"
#include "TMPSensor.h"
#include "MachineModelSingleton.h"
#include "MachineModel.h"
#include "Servo.h"
#define TCHECK 80
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
    long elapsed;
    TMPSensor* tmpSensor;
    Servo* servo;
    Display *display;
    int angle;
    int delta;
    bool to180;
    bool to0;
    bool motorTest;
    bool tempTest;
    bool checkTempExecuted;
    bool* sleeping;

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
        checkTempExecuted = true;
        double temp = tmpSensor->getValue();
        if (temp > TMAX || temp < TMIN)
        {
            checkState = Assistance;
            tempTest = false;
            display->print("Assistance required");
            MachineModelSingleton::getInstance()->setAssistanceState();
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
        checkTempExecuted = false;
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
    void setDependencies(bool* sleeping){
        this->sleeping = sleeping;
    }

    void tick()
    {
        switch (checkState)
        {
        case Off:
            //Serial.println("check task off");
            elapsed += Task::myPeriod;
            if (elapsed > TCHECK*1000L  && MachineModelSingleton::getInstance()->getMachineState() == Idle && !(*sleeping))
            {
                checkState = On;
                servo->on();
                display->print("Check test");
                MachineModelSingleton::getInstance()->incrementNTest();
            }
            break;
        case On:

            //Serial.println("check on");

            if(!checkTempExecuted){
                checkTmp();
            }
            testMotor();
            if (motorTest && tempTest && checkState == On)
            {
                checkState = Off;
                initVars();
                servo->off();
                elapsed = 0;
                display->print("Ready");
            } 
            break;
        case Assistance:
            //Serial.println("check assistance");
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