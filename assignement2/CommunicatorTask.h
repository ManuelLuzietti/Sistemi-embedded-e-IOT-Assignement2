#ifndef __COMMUNICATORTASK__
#define __COMMUNICATOR__
#include "MsgService.h"
#include "MachineModelSingleton.h"
#include "MachineModel.h"

class CommunicatorTask : public Task
{
    enum CommunicatorStates
    {
        On
    }
    communicatorState;

public:
    void init(int period)
    {
        Task::init(period);
        communicatorState = On;
        MsgService.init();
    }
    void tick()
    {
        MachineModel* machineModel = MachineModelSingleton::getInstance();
        switch (communicatorState)
        {
        case On:
            if (MsgService.isMsgAvailable())
            {
                Msg *msg = MsgService.receiveMsg();
                //Serial.println(msg->getContent());
                if(msg->getContent() == "1"){
                    machineModel->refill();
                } else if (msg->getContent() == "2"){
                    machineModel->recover();
                }
                /* NOT TO FORGET: msg deallocation */
                delete msg;
            }
            MachineModel* machineModel = MachineModelSingleton::getInstance();
            String message = machineModel->getStatus() + " " +machineModel->getNproducts() + " " 
                + machineModel->getNTest()+ " ";
            MsgService.sendMsg(message);
            break;

        default:
            break;
        }
    }
};

#endif