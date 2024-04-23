#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

#define FPS         10

class Game {
public:
    virtual void setup() = 0;
    virtual void run() = 0;

protected:
    unsigned long ticks;

    const unsigned long frameTime = 1000 / FPS;
    unsigned long startTime;
    int delayTime;
    
    bool isRunning;

    virtual void start() = 0;
    virtual void readInputs() = 0;
    virtual void update() = 0;
    virtual void drawScreen() = 0;
};

#endif // GAME_H
