#ifndef __READYTASK__
#define __READYTASK__
#include "Display.h"
#include <avr/sleep.h>
#include "MachineModelSingleton.h"
#include "MachineModel.h"
#include "EnableInterrupt.h"

#define TIDLE 60000

void wakeUp(void)
{
}
class ReadyTask : public Task
{
    Display *display;
    bool *displaying;
    bool *initEnd;
    bool *making;
    bool *waiting;
    bool *removed;
    bool readyOn;
    enum ReadyState
    {
        On,
        Off,
        Waiting,
        Sleep
    } readyState;
    int elapsed;
    int pirPin;

public:
    ReadyTask(int pirPin):pirPin(pirPin)
    {}

    void setDependencies(bool *displaying, bool *initEnd, bool *making, bool *waiting, bool *removed)
    {
        this->displaying = displaying;
        this->initEnd = initEnd;
        this->making = making;
        this->waiting = waiting;
        this->removed = removed;
    }
    void initVars()
    {
        // nel caso si inizializzino delle vars
        elapsed = 0;
    }
    void init(int period)
    {
        Task::init(period);
        display = new Display(0x27, 16, 2);
        readyState = Off;
        initVars();
    }
    void tick()
    {
        switch (readyState)
        {
        case Sleep:
            display->print("sleeping..");
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            enableInterrupt(pirPin, wakeUp, HIGH);
            sleep_mode();
            sleep_disable();
            disableInterrupt(pirPin);
            Serial.println("woke up");
            readyState = On;
            elapsed = 0;
            display->print("Ready");
            break;
        case Waiting:
            Serial.println("Ready Waiting");
            if (*removed && *waiting)
            {
                initVars();
                readyState = On;
                display->print("Ready");
            }
            break;
        case On:
            if(MachineModelSingleton::getInstance()->getMachineState()== Assistance){
                readyState = Off;
                break;
            }
            Serial.println("Ready On");
            readyOn = true;
            if (MachineModelSingleton::getInstance()->getMachineState() == Idle)
            {
                elapsed += Task::myPeriod;
            }
            if (elapsed > TIDLE)
            {
                readyState = Sleep;
                Serial.println(String("Ready On to sleep ") + elapsed);
            }
            if ((*displaying) || !(*initEnd))
            {
                readyState = Off;
            }
            if ((*making))
            {
                readyState = ReadyState::Waiting;
            }

            break;
        case Off:
            Serial.println("Ready Off");
            if(MachineModelSingleton::getInstance()->getMachineState() == Assistance){
                display->print("Assistance required");
            }
            if (!(*displaying) && (*initEnd) && !(*making) && !(*waiting) && MachineModelSingleton::getInstance()->getMachineState() != Assistance)
            {
                readyState = On;
                elapsed = 0;
                display->print("Ready");
            }
            break;
        }
    }

    void activate()
    {
        readyState = On;
    }
    void deactivate()
    {
        readyState = Off;
    }

    bool *getReadyOn()
    {
        return &readyOn;
    }
};

#endif