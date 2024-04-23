#include <Arduino.h>

#include "SpaceInvaders.h"     // Include your games
#include "Demo.h"

SpaceInvaders spaceInvaders;    // Instantiate your game
// Demo demo;                   // (only one at the same time)

void setup() {
    Serial.begin(115200);
    delay(10);

    spaceInvaders.setup();     // Set up your game
}

void loop() {
    spaceInvaders.run();       // Run your game
}