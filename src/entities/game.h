#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "shared/primitives.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Size2D size;
    float fps;
    float delta_time;
    GameState state;
    int running;
    SDL_Color background_color;
} Game;

#endif
