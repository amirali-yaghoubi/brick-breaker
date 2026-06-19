#include "paddle.h"
#include <SDL2/SDL.h>
#include "entities/paddle.h"

void paddle_update(World *world, Game *game) {
    int mouse_x, mouse_y;

    SDL_GetMouseState(&mouse_x, &mouse_y);
    
    world->paddle->position.x = mouse_x - world->paddle->size.w / 2;

    if (world->paddle->position.x <= 0) {
        world->paddle->position.x = 0;
    }
    
    if (world->paddle->position.x + world->paddle->size.w >= game->size.w) {
        world->paddle->position.x = game->size.w - world->paddle->size.w;
    }
}
