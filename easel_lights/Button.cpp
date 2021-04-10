#include "Button.h"

Button::Button(byte pin) {
  this->pin = pin;
  this->pin_mode = INPUT; // Assume INPUT if not specified
  
  // Using INPUT_PULLUP, so everything is flipped.
  //lastReading = LOW;
  lastReading = HIGH;
  init();
}

Button::Button(byte pin, byte pin_mode, bool isInterruptButton, long debounceDelay) {
  this->pin = pin;
  this->pin_mode = pin_mode;
  this->isInterruptButton = isInterruptButton;
  this->debounceDelay = debounceDelay;

  if (pin_mode == INPUT_PULLUP) {
    // Using INPUT_PULLUP, so everything is flipped, i.e. HIGH == not pressed
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
  bool result = false;
  // The logic for determining a button press differs when the button triggers an interrupt (the if clause)
  //   vs when we're trying to detect a button press in the loop (the else clause).
  // I'm not sure why this is the case, but this code works in those two scenarios.
  if (isInterruptButton) {
    if ((millis() - lastDebounceTime) >= debounceDelay) {
      result = true;
      // not sure if this should be current millis() or millis() from the if statement above.
      lastDebounceTime = millis();
    }
  }
  else {
    if (pin_mode == INPUT_PULLUP) {
      // Using INPUT_PULLUP, so everything is flipped.
      result = (getState() == LOW);
    }
    else {
      result = (getState() == HIGH);
    }
  }
  return result;
}

void Button::printStatus() {
  Serial.print("debounceDelay: ");
  Serial.println(debounceDelay);
  Serial.print("lastDebounceTime: ");
  Serial.println(lastDebounceTime);
}
