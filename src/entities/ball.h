#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "shared/primitives.h"

typedef struct {
    Vector2D position;
    Vector2D velocity;
    float speed;
    SDL_Color color;
    float radius;
} Ball;

#endif
