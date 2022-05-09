#ifndef __INITTASK__
#define __INITTASK__
#define NMAX 10
#define NPROD 3
#include "Display.h"

class InitTask : public Task
{
    /*int nproducts = NPROD;
    int qty[NPROD];
    int sugarLevel;
    String productNames[NPROD] = {"Coffe","Tea","Chocolate"};
    int maxQtyProd = NMAX;*/
    Display *display;

    /* enum MachineStates
    {
        Idle,
        Working,
        Assistance
    } machineState; */

    enum TaskState
    {
        On,
        Off
    } taskState;

    /* enum Products
    {
        Coffe,
        Tea,
        Chocolate
    } productSel; */

    
public:
    void init(int period)
    {
        Task::init(period);
        //machineState = Idle;
        taskState = On;
        display = new Display(0x27, 16, 2);
        /* for (int i = 0; i < nproducts; i++)
        {
            qty[i] = maxQtyProd;
        }
        sugarLevel = 0;
        productSel = Coffe; */
    }

    void tick()
    {
        switch (taskState)
        {
        case On:
            display->print("Welcome");
            deactivate();
            break;
        default:
            break;
        }
    }

    /* void setWorkingState()
    {
        machineState = Working;
    }

    void setIdleState()
    {
        machineState = Idle;
    }

    void setAssistanceState()
    {
        machineState = Assistance;
    } */


    /* void selectNextProduct(){
        productSel = (productSel + 1) % nproducts;
    }
    void selectPrevProduct(){
        productSel = (productSel-1 == -1) ? nproducts-1 : productSel - 1;
        Serial.println(productSel);
    }

    String getSelectedProduct(){
        return productNames[productSel];
    } */

    void isActive(){
        return taskState == On;
    }
    
    private:
    void activate()
    {
        taskState = On;
    }

    void deactivate()
    {
        taskState = Off;
    }


};

#endif