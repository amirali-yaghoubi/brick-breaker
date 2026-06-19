#ifndef BRICKS_H
#define BRICKS_H

#include <SDL2/SDL.h>
#include "shared/primitives.h"

typedef struct {
    Vector2D position;
    int hp;
    SDL_Color color;
} Brick;

typedef struct {
    Brick *members;
    Size2D size;
    Vector2D padding;
    int cols;
    int rows;
} Bricks;

int generate_bricks_array(Bricks *bricks);
void free_bricks(Bricks *bricks);


#endif
