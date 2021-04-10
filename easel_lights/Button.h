#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>

class Button {
  
  private:
    byte pin;
    byte state;
    byte lastReading;
    byte pin_mode;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
    bool isInterruptButton = false;
    
  public:
    Button(byte pin);
    Button(byte pin, byte pin_mode, bool isInterruptButton, long debounceDelay);

    void init();
    void update();

    byte getState();
    bool isPressed();

    void printStatus();
};

#endif
