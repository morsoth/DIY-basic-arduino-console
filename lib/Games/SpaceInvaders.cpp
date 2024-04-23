#include "SpaceInvaders.h"

#include "Button.h"
#include "Joystick.h"

#include "Sprites.h"

Button redButton(5);
Button blueButton(6);
Joystick joystick(A0, A1);

void SpaceInvaders::setup() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_5x7_tf);

    redButton.begin();
    blueButton.begin();
    joystick.begin();
}

void SpaceInvaders::start() {
    ticks = 0;
    isRunning = true;

    canShoot = true;
    enemyDir = RIGHT;
    enemyMoveDown = false;
    enemyMoveTicks = 0;
    enemyUpdateTicks = 20;
    enemiesAlive = true;
    score = 0;

    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            if (i == 7 and j == 0) screen[i][j] = PLAYER;
            else if (i == 1 and j%2 == 0 and j < 11) screen[i][j] = ALIEN_3;
            else if (i == 2 and j%2 == 0 and j < 11) screen[i][j] = ALIEN_2;
            else if ((i == 3 or i == 4) and j%2 == 0 and j < 11) screen[i][j] = ALIEN_1;
            else if (i == 6 and (j-1)%4 == 0) screen[i][j] = ROCK_LEFT;
            else if (i == 6 and (j-2)%4 == 0) screen[i][j] = ROCK_RIGHT;
            else screen[i][j] = VOID;
        }
    }
}

void SpaceInvaders::readInputs() {
    redButton.read();
    blueButton.read();
    joystick.read();
}

void SpaceInvaders::update() {
    if (reloadTicks > 0) --reloadTicks;
    else if (reloadTicks == 0) canShoot = true;

    enemiesAlive = false;
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            switch (screen[i][j]) {
                case ALIEN_1:
                case ALIEN_2:
                case ALIEN_3:
                    if (enemyMoveTicks%enemyUpdateTicks == 0) {
                        if (enemyMoveDown) {}
                        else if (enemyDir == RIGHT) {
                            if (screen[i][j+1] == PLAYER_BULLET) {
                                screen[i][j+1] = VOID;
                                score += (10 * screen[i][j]);
                            }
                            else screen[i][j+1] = screen[i][j];
                            screen[i][j] = VOID;
                            ++j;
                        }
                        else if (enemyDir == LEFT) {
                            if (screen[i][j-1] == PLAYER_BULLET) {
                                screen[i][j-1] = VOID;
                                score += (10 * screen[i][j]);
                            }
                            else screen[i][j-1] = screen[i][j];
                            screen[i][j] = VOID;
                        }
                    }
                    enemiesAlive = true;
                    break;
                case PLAYER_BULLET:
                    screen[i][j] = VOID;
                    if (screen[i-1][j] == ALIEN_1 or screen[i-1][j] == ALIEN_2 or screen[i-1][j] == ALIEN_3) {
                        score += (10 * screen[i-1][j]);
                        screen[i-1][j] = VOID;
                    }
                    else if (i > 0) {
                        screen[i-1][j] = PLAYER_BULLET;
                    }
                    break;
                case PLAYER:
                    if (joystick.right() and j < SCREEN_WIDTH-1) {
                        screen[i][j] = VOID;
                        screen[i][++j] = PLAYER;
                    }
                    else if (joystick.left() and j > 0) {
                        screen[i][j] = VOID;
                        screen[i][--j] = PLAYER;
                    }

                    if (redButton.buttonDown() and canShoot) {
                        if (screen[i-1][j] == ROCK_LEFT or screen[i-1][j] == ROCK_RIGHT) {
                            screen[i-1][j] = VOID;
                        }
                        else {
                            screen[i-1][j] = PLAYER_BULLET;
                        }
                        canShoot = false;
                        reloadTicks = 2;
                    }
                    break;
            }
        }
    }

    if (enemyMoveTicks%enemyUpdateTicks == 0) {
        if (enemyMoveDown) {
            for (int i = SCREEN_HEIGHT-2; i >= 0; --i) {
                for (int j = 0; j < SCREEN_WIDTH; ++j) {
                    if (isAlien(screen[i][j])) {
                        if (i+1 == 6) isRunning = false;
                        screen[i+1][j] = screen[i][j];
                        screen[i][j] = VOID;
                    }
                }
            }
            enemyMoveDown = false;
            if (enemyDir == RIGHT) enemyDir = LEFT;
            else if (enemyDir == LEFT) enemyDir = RIGHT;
            enemyMoveTicks = 0;
            enemyUpdateTicks -= 3;
        }
        else if (enemyDir == RIGHT) {
            for (int i = 0; i < SCREEN_HEIGHT; ++i) {
                if (isAlien(screen[i][SCREEN_WIDTH-1]))
                    enemyMoveDown  = true;
            }
        }
        else if (enemyDir == LEFT) {
            for (int i = 0; i < SCREEN_HEIGHT; ++i) {
                if (isAlien(screen[i][0]))
                    enemyMoveDown  = true;
            }
        }
    }
    ++enemyMoveTicks;

    if (enemiesAlive == false) isRunning = false;
}

void SpaceInvaders::drawScreen() {
    u8g2.firstPage();
    do {

    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j)
            drawSprite(spaceInvadersSprites, screen[i][j], j*SPRITE_WIDTH, i*SPRITE_HEIGHT, SPRITE_HEIGHT, SPRITE_WIDTH);
    }

    u8g2.drawStr(2, 6, "Score:");
    u8g2.setCursor(34, 6);
    u8g2.print(score);

    } while (u8g2.nextPage());
}

void SpaceInvaders::drawStartScreen() {
    u8g2.firstPage();
    do {

    u8g2.setFont(u8g2_font_DigitalDisco_tf);
    u8g2.drawStr(8, 15, "SPACE INVADERS");
    u8g2.setFont(u8g2_font_5x7_tf);
    u8g2.drawStr(31, 30, "-SCORE TABLE-");
    drawSprite(spaceInvadersSprites, ALIEN_3, 35, 32, SPRITE_HEIGHT, SPRITE_WIDTH);
    u8g2.drawStr(44, 40, "=30 POINTS");
    drawSprite(spaceInvadersSprites, ALIEN_2, 35, 42, SPRITE_HEIGHT, SPRITE_WIDTH);
    u8g2.drawStr(44, 50, "=20 POINTS");
    drawSprite(spaceInvadersSprites, ALIEN_1, 35, 52, SPRITE_HEIGHT, SPRITE_WIDTH);
    u8g2.drawStr(44, 60, "=10 POINTS");
    
    } while (u8g2.nextPage());
}

void SpaceInvaders::drawEndScreen() {
    u8g2.firstPage();
    do {
    
    // WIN
    if (enemiesAlive == false) {
        u8g2.setFont(u8g2_font_DigitalDisco_tf);
        u8g2.drawStr(35, 24, "YOU WIN");
        u8g2.setFont(u8g2_font_5x7_tf);
        u8g2.drawStr(18, 34, "Your planet is safe");
    }
    // LOSE
    else {
        u8g2.setFont(u8g2_font_DigitalDisco_tf);
        u8g2.drawStr(25, 24, "GAME OVER");
        u8g2.setFont(u8g2_font_5x7_tf);
        drawSprite(spaceInvadersSprites, ALIEN_1, 49, 27, SPRITE_HEIGHT, SPRITE_WIDTH);
        drawSprite(spaceInvadersSprites, ALIEN_2, 62, 27, SPRITE_HEIGHT, SPRITE_WIDTH);
        drawSprite(spaceInvadersSprites, ALIEN_3, 75, 27, SPRITE_HEIGHT, SPRITE_WIDTH);
    }
    u8g2.drawStr(39, 50, "Score:");
    u8g2.setCursor(71, 50);
    u8g2.print(score);

    } while (u8g2.nextPage());
}

bool SpaceInvaders::isAlien(char c) {
    return (c == ALIEN_1 or c == ALIEN_2 or c == ALIEN_3);
}

void SpaceInvaders::run() {
    Serial.println(F("Game started."));
    drawStartScreen();
    delay(3000);

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
    drawEndScreen();
    delay(5000);
}