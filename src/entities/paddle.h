#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
#include "shared/primitives.h"

typedef struct {
    Vector2D position;
    Size2D size;
    SDL_Color color;
} Paddle;

#endif
