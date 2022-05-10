#ifndef __MACHINEMODELSINGLETON__
#define __MACHINEMODELSINGLETON__
#include "MachineModel.h"

 class MachineModelSingleton{
    private:
    static MachineModel* machineModel = NULL;

    public:
        static void init(){
            getInstance();
        }
        static MachineModel* getInstance(){
            if(machineModel == NULL){
                machineModel = new MachineModel();
            }
            return machineModel;
        }
};
MachineModel* MachineModelSingleton::machineModel; //wtf
#endif