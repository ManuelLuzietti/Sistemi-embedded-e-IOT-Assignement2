#include "Display.h"

Display::Display(uint8_t addr,uint8_t col,uint8_t row){
    this->lcd = new  LiquidCrystal_I2C(addr,col,row);
    this->lcd->init();
    this->lcd->backlight();
}

void Display::print(char* string){
    this->lcd->clear();
    this->lcd->setCursor(0,0);
    this->lcd->print(string);
}

void Display::print(String string){
    this->lcd->clear();
    this->lcd->setCursor(0,0);
    this->lcd->print(string);
}