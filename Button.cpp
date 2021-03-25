#include "Button.h"

Button::Button(byte pin) {
  this->pin = pin;
  this->pin_mode = INPUT; // Assume INPUT if not specified
  
  // Using INPUT_PULLUP, so everything is flipped.
  //lastReading = LOW;
  lastReading = HIGH;
  init();
}

Button::Button(byte pin, byte pin_mode) {
  this->pin = pin;
  this->pin_mode = pin_mode;

  if (pin_mode == INPUT_PULLUP) {
    // Using INPUT_PULLUP, so everything is flipped.
    lastReading = HIGH;
  }
  else {
    lastReading = LOW;
  }
  init();
}

void Button::init() {
  pinMode(pin, pin_mode);
  update();
}

void Button::update() {
    // You can handle the debounce of the button directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    byte newReading = digitalRead(pin);
    
    if (newReading != lastReading) {
      lastDebounceTime = millis();
    }

    if (millis() - lastDebounceTime > debounceDelay) {
      // Update the 'state' attribute only if debounce is checked
      state = newReading;
    }

    lastReading = newReading;
}

byte Button::getState() {
  update();
  return state;
}

bool Button::isPressed() {
  if (pin_mode == INPUT_PULLUP) {
    // Using INPUT_PULLUP, so everything is flipped.
    return (getState() == LOW);
  }
  else {
    return (getState() == HIGH);
  }
}
