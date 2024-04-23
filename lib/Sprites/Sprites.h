#ifndef SPRITES_H
#define SPRITES_H

#include <Arduino.h>
#include <SPI.h>

#include "U8g2lib.h"

U8G2_ST7920_128X64_2_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

void drawSprite(const byte *spriteSheet, char sprite, int x, int y, int h, int w) {
    if (spriteSheet == NULL or sprite < 0) return;
    if (h > 8) h = 8;

    for (int i = 0; i < w; ++i) {
        byte b = spriteSheet[sprite*w+i];
        for (int j = 0; j < h; ++j) {
            if (b & 0x1) u8g2.drawPixel(x+i, y+j);
            b = b >> 1;
        }
    }
}

#define VOID           -1
#define PLAYER          0
#define ALIEN_1         1
#define ALIEN_2         2
#define ALIEN_3         3
#define ROCK_LEFT       4
#define ROCK_RIGHT      5
#define PLAYER_BULLET   6

const byte spaceInvadersSprites[56] = {
    0xE0, 0xE0, 0xF0, 0xFC, 0xFC, 0xF0, 0xE0, 0xE0,                   // PLAYER
    0xBC, 0xB6, 0xB6, 0x5F, 0x5F, 0xB6, 0xB6, 0xBC,                   // ALIEN 1
    0x38, 0xFD, 0xB6, 0x3C, 0x3C, 0xB6, 0xFD, 0x38,                   // ALIEN 2
    0x98, 0x5C, 0xB6, 0x5F, 0x5F, 0xB6, 0x5C, 0x98,                   // ALIEN 3
    0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x3F,                   // ROCK LEFT
    0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,                   // ROCK RIGHT
    0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00,                   // PLAYER BULLET
};

// Define your sprites here

// Declare your sprite sheets here
// (to learn how sprite work read the README.md file)

#endif // SPRITES_H