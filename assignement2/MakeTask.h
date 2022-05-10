#ifndef __MAKETASK__
#define __MAKETASK__
#include "Servo.h"
#define TMAKING 5
class MakeTask : public Task
{
    enum MakeStates
    {
        Off,
        On,
        Ready
    } makeState;
    Servo *servo;
    int angle;
    bool *selectEnd;
    Display *display;
    int delta;
    bool makeEnd;
    bool making;
    bool prodReady;
    bool *removed;

public:
    MakeTask(int servoPin)
    {
        servo = new Servo(servoPin);
    }
    void setDependencies(bool *selectEnd, bool *removed)
    {
        this->selectEnd = selectEnd;
        this->removed = removed;
    }
    void initVars()
    {
        makeEnd = false;
        making = false;
        prodReady = false;
        angle = 0;
    }
    void init(int period)
    {
        Task::init(period);
        makeState = Off;
        initVars();
        display = new Display(0x27, 16, 2);
    }

    void tick()
    {
        switch (makeState)
        {
        case Ready:
            //Serial.println("Make ready");
            if (*removed)
            {
                initVars();
                makeState = Off;
                servo->setPosition(angle);
                servo->off();
            }
            break;
        case Off:
            //Serial.println("Make off");
            if ((*selectEnd) && !makeEnd && !(*removed))
            {
                makeState = On;
                servo->on();
                making = true;
                display->print(String("making ") + MachineModelSingleton::getInstance()->getSelectedProduct());
                MachineModelSingleton::getInstance()->setWorkingState();
            }
            break;
        case On:
            // Serial.println("Make On");
            if (angle < 180)
            {
                angle++;
                servo->setPosition(angle);
            }
            else
            {
                makeState = Ready;
                makeEnd = true;
                making = false;
                angle = 0;
                prodReady = true;
            }
            break;
        }
    }

    bool *getMakeEnd()
    {
        return &makeEnd;
    }
    bool *getMaking()
    {
        return &making;
    }
    bool *getProdReady()
    {
        return &prodReady;
    }
};

#endif