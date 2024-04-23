#include "Demo.h"

#include "Button.h"
#include "Joystick.h"

#include "Sprites.h"

// Declare your peripherals here
Button redButton(5);
Button blueButton(6);
Joystick joystick(A0, A1);

void Demo::setup() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_5x7_tf);

    redButton.begin();
    blueButton.begin();
    joystick.begin();

    // Set up your peripherals here
}

void Demo::start() {
    ticks = 0;
    isRunning = true;

    // Initialize your variables here
}

void Demo::readInputs() {
    redButton.read();
    blueButton.read();
    joystick.read();

    // Read your inputs here
}

void Demo::update() {
    // Process your inputs and update your variables here
}

void Demo::drawScreen() {
    u8g2.firstPage();
    do {

    // Draw to the display here

    } while (u8g2.nextPage());
}

void Demo::run() {
    Serial.println(F("Game started."));

    start();
    while (isRunning) {
        startTime = millis();

        readInputs();

        update();

        drawScreen();

        ++ticks;

        delayTime = frameTime - (millis() - startTime);

        if (delayTime > 0) delay(delayTime);
    }
    Serial.println(F("Game ended."));
    delay(5000);
}