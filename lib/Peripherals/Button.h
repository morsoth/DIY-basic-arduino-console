#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
private:
    int pin;
    bool currentState, lastState;
    
public:
    Button(int _pin);

    void begin();
    void read();
    bool isPressed();
    bool buttonDown();
    bool buttonUp();
};

Button::Button(int _pin) : pin(_pin), currentState(false), lastState(false) {}

void Button::begin() {
    pinMode(pin, INPUT);
}

void Button::read() {
    lastState = currentState;
    currentState = digitalRead(pin);
}

bool Button::isPressed() { return currentState; }

bool Button::buttonDown() { return currentState and not lastState; }

bool Button::buttonUp() { return not currentState and lastState; }

#endif // BUTTON_H
