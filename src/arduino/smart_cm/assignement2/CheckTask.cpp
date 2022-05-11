#include "CheckTask.h"
void CheckTask::testMotor()
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
            this->motorTest = true;
        }
    }