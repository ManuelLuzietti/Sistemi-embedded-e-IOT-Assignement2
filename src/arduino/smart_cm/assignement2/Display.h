#ifndef __DISPLAY__
#define __DISPLAY__
#include <LiquidCrystal_I2C.h>

class Display{
    public:
        Display(uint8_t addr,uint8_t col,uint8_t row);
        void print(char* string);
        void print(String string);
    private:
        LiquidCrystal_I2C* lcd;
        uint8_t addr;
};


#endif 