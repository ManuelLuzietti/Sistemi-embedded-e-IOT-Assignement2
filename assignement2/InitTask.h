#ifndef __INITTASK__
#define __INITTASK__
#define NMAX 10
#define NPROD 3
#include "Display.h"
#include "MachineModelSingleton.h"

class InitTask : public Task
{
    Display *display;
    int elapsed;

    enum InitStates
    {
        On,
        Off
    } initState;
    bool initEnd;

    
public:
    void init(int period)
    {
        Task::init(period);
        initState = On;
        display = new Display(0x27, 16, 2);
        MachineModelSingleton::getInstance()->init();
        elapsed = 0;
        initEnd = false;
    }

    void tick()
    {
        switch (initState)
        {           

        case On:
            //Serial.println("Init On");
            elapsed += Task::myPeriod;
            if(elapsed >= 2000){
                deactivate();
                elapsed = 0;
            }
            display->print("Welcome");
            break;
        default:
            //Serial.println("Init Off");
            break;
        }
    }

    void isActive(){
        return initState == On;
    }
    bool* getInitEnd(){
        return &initEnd;
    }
    
private:
    void activate()
    {
        initState = On;
    }

    void deactivate()
    {
        initState = Off;
        initEnd = true;
    }


};

#endif