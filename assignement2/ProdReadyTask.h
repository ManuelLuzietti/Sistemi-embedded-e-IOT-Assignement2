#ifndef __PRODREADYTASK__
#define __PRODREADYTASK__
#include "Sonar.h"
#include "Task.h"
#include "Display.h"
#define TTIMEOUT 10
class ProdReadyTask : public Task
{
    Sonar *sonar;
    bool *prodReady;
    bool *readyOn;
    bool waiting;
    long elapsed;
    bool removedVar;
    Display *display;
    bool glassRemoved;
    enum class PReadyStates
    {
        On,
        Off,
        Removed
    } pReadyState;

    void initVars()
    {
        waiting = false;
        elapsed = 0;
        pReadyState = PReadyStates::Off;
    }

    bool isGlassRemoved()
    {
        glassRemoved = sonar->getDistance() > 0.4;
    }

public:
    void setDependencies(bool *prodReady, bool *readyOn)
    {
        this->prodReady = prodReady;
        this->readyOn = readyOn;
    }
    ProdReadyTask(int sonarPinTrig, int sonarPinEcho)
    {
        sonar = new Sonar(sonarPinTrig, sonarPinEcho);
    }
    void init(int period)
    {
        Task::init(period);
        display = new Display(0x27, 16, 2);
        removedVar = false;
        initVars();
    }

    void tick()
    {
        switch (pReadyState)
        {
        case PReadyStates::Off:
            //Serial.println("PreadyOff");
            removedVar = false;
            if ((*prodReady))
            {
                //Serial.println("prdReady true");
                pReadyState = PReadyStates::On;
                display->print(String("The " + MachineModelSingleton::getInstance()->getSelectedProduct() + " is ready!"));
                waiting = true;
            }
            break;
        case PReadyStates::On:
            //Serial.println("Pready On");
            elapsed += Task::myPeriod;
            isGlassRemoved();
            if (elapsed > TTIMEOUT * 1000L || glassRemoved)
            {
                //Serial.println("ok");
                elapsed = 0;
                // waiting = false;
                removedVar = true;
                pReadyState = PReadyStates::Removed;
            }
            break;
        case PReadyStates::Removed:
            if ((*readyOn) && !(*prodReady))
            {
                initVars();
                pReadyState = PReadyStates::Off;
                //Serial.println("removed glass");
                display->print("Ready");
            }
        }
    }
    bool *getWaiting()
    {
        return &waiting;
    }
    bool *getRemoved()
    {
        return &removedVar;
    }
};

#endif