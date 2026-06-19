#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include "ball.h"
#include "paddle.h"
#include "bricks.h"

typedef struct {
    Ball *ball;
    Paddle *paddle;
    Bricks *bricks;
} World;

#endif
