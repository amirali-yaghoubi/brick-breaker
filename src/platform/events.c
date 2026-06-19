#include "events.h"
#include <SDL2/SDL.h>


void handle_events(World *world, Game *game) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            game->running = 0;
        }
    }
}
