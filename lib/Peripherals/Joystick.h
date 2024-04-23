#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

class Joystick {
private:
    int pinX, pinY;
    int x, y;

public:
    Joystick(int _pinX, int _pinY);

    void begin();
    void read();
    int getX();
    int getY();
    bool up();
    bool down();
    bool left();
    bool right();
};

Joystick::Joystick(int _pinX, int _pinY) : pinX(_pinX), pinY(_pinY), x(0), y(0) {}

void Joystick::begin() {
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
}

void Joystick::read() {
    x = analogRead(pinX);
    y = analogRead(pinY);
}

int Joystick::getX() {
    return x;   // Range 0 - 1023
}

int Joystick::getY() {
    return y;   // Range 0 - 1023
}

bool Joystick::up() {
    return y >= 550;
}

bool Joystick::down() {
    return y <= 450;
}

bool Joystick::left() {
    return x <= 450;
}

bool Joystick::right() {
    return x >= 550;
}

#endif // JOYSTICK_H
