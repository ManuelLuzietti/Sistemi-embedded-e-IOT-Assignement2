#ifndef __SELECTTASK__
#define __SELECTTASK__
#include "ButtonImpl.h"
#include "Potentiometer.h"
#include "InitTask.h"
#include "Display.h"

class SelectTask : public Task
{
    ButtonImpl *btnUp;
    ButtonImpl *btnDown;
    ButtonImpl *btnMake;
    Potentiometer *sugarPot;
    Display *display;
    int elapsed;
    bool *initEnd;
    bool displaying;
    bool selectEnd;
    String prevSelectedProd;
    int prevSugarLevel;
    int sugarLevel;
    int sugarValue;
    bool *removed;
    enum SelectStates
    {
        Off,
        On,
        Displaying,
        Selected
    } selectState;

public:
    SelectTask(int upPin, int dwnPin, int makePin, int potPin)
    {
        btnUp = new ButtonImpl(upPin);
        btnDown = new ButtonImpl(dwnPin);
        btnMake = new ButtonImpl(makePin);
        sugarPot = new Potentiometer(potPin);
    }
    void setDependencies(bool *initEnd, bool *removed)
    {
        this->initEnd = initEnd;
        this->removed = removed;
    }
    void initVars()
    {
        elapsed = 0;
        displaying = false;
        selectEnd = false;
        prevSelectedProd = "";
        prevSugarLevel = 0;
        sugarValue = sugarPot->getValue();
        prevSugarLevel = map(sugarValue, 0, 1023, 0, 3);
        MachineModelSingleton::getInstance()->setSugarLevel(prevSugarLevel);
    }
    void init(int period)
    {
        Task::init(period);
        selectState = Off;
        display = new Display(0x27, 16, 2);
        initVars();

        // sugarLevel = 0;
    }

    void tick()
    {
        String selectedProd;

        switch (selectState)
        {
        case Selected:
            // Serial.println("Select Selected");
            if (*removed)
            {
                initVars();
                selectState = Off;
            }
            break;
        case SelectStates::Off:
            // Serial.println("Select Off");
            if ((*initEnd) && (!selectEnd) && MachineModelSingleton::getInstance()->getMachineState() != Assistance)
            {
                selectState = On;
            }
            break;
        case SelectStates::On:
            // Serial.println("Select On");
            if (MachineModelSingleton::getInstance()->getMachineState() == Assistance)
            {
                selectState = Off;
                display->print("Assistance required");
                break;
            }
            if (btnUp->isPressed())
            {
                displaying = true;
                selectState = Displaying;
                MachineModelSingleton::getInstance()->selectNextProduct();
                MachineModelSingleton::getInstance()->setWorkingState();
            }
            else if (btnDown->isPressed())
            {
                displaying = true;
                selectState = Displaying;
                MachineModelSingleton::getInstance()->selectPrevProduct();
                MachineModelSingleton::getInstance()->setWorkingState();
            }

            if (btnMake->isPressed())
            {
                selectState = Selected;
                displaying = false;
                selectEnd = true;
                elapsed = 0;
                MachineModelSingleton::getInstance()->selectCurrentProduct();
                MachineModelSingleton::getInstance()->setWorkingState();

                break;
            }
            sugarValue = sugarPot->getValue();
            sugarLevel = map(sugarValue, 0, 1023, 0, 3);

            if (sugarLevel != prevSugarLevel)
            {
                MachineModelSingleton::getInstance()->setSugarLevel(sugarLevel);
                MachineModelSingleton::getInstance()->setWorkingState();

                displaying = true;
                selectState = Displaying;
            }
            break;
        case SelectStates::Displaying:

            // Serial.println("Select Displaying");
            if (MachineModelSingleton::getInstance()->getMachineState() == Assistance)
            {
                selectState = Off;
                display->print("Assistance required");
                initVars();
                break;
            }
            if (btnMake->isPressed())
            {
                selectState = Selected;
                displaying = false;
                selectEnd = true;
                elapsed = 0;
                MachineModelSingleton::getInstance()->selectCurrentProduct();
                break;
            }
            elapsed += this->myPeriod;
            selectedProd = MachineModelSingleton::getInstance()->getSelectedProduct();
            sugarLevel = MachineModelSingleton::getInstance()->getSugarLevel();
            if (sugarLevel != prevSugarLevel)
            {
                display->print(String("Sugar level: ") + sugarLevel);
                prevSugarLevel = sugarLevel;
            }
            if (selectedProd != prevSelectedProd)
            {
                display->print(selectedProd);
                prevSelectedProd = selectedProd;
            }
            sugarValue = sugarPot->getValue();
            sugarLevel = map(sugarValue, 0, 1023, 0, 3);
            if (sugarLevel != prevSugarLevel)
            {
                MachineModelSingleton::getInstance()->setSugarLevel(sugarLevel);
                elapsed = 0;
            }

            if (btnUp->isPressed())
            {
                MachineModelSingleton::getInstance()->selectNextProduct();
                elapsed = 0;
            }
            else if (btnDown->isPressed())
            {
                elapsed = 0;
                MachineModelSingleton::getInstance()->selectPrevProduct();
            }
            if (elapsed >= 5000)
            {
                elapsed = 0;
                selectState = SelectStates::On;
                displaying = false;
            }
            break;
        }
    }

    bool *getDisplaying()
    {
        return &displaying;
    }
    bool *getSelectEnd()
    {
        return &selectEnd;
    }
};

#endif