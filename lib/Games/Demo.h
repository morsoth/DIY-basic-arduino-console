#ifndef DEMO_H
#define DEMO_H

#include "Game.h"

// Define your defines here

// Create your new classes here

class Demo : public Game {
private:
    // Declare your variables and methods here

public:
    virtual void setup();
    virtual void run();

protected:
    virtual void start();
    virtual void readInputs();
    virtual void update();
    virtual void drawScreen();
};

#endif // DEMO_H
