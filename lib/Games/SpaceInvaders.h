#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include "Game.h"

#define SCREEN_WIDTH    16
#define SCREEN_HEIGHT   8
#define SPRITE_WIDTH    8
#define SPRITE_HEIGHT   8

enum Dir { LEFT, RIGHT };

class SpaceInvaders : public Game {
private:
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    bool canShoot;
    byte reloadTicks;
    Dir enemyDir;
    bool enemyMoveDown;
    byte enemyMoveTicks;
    byte enemyUpdateTicks;
    bool enemiesAlive;
    int score;

    void drawStartScreen();
    void drawEndScreen();

    bool isAlien(char c);

public:
    virtual void setup();
    virtual void run();

protected:
    virtual void start();
    virtual void readInputs();
    virtual void update();
    virtual void drawScreen();

};

#endif // SPACEINVADERS_H
