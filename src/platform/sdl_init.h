#ifndef SDL_INIT_H
#define SDL_INIT_H

#include "entities/game.h"

int init_sdl(Game *game);
void cleanup_sdl(Game *game);

#endif
