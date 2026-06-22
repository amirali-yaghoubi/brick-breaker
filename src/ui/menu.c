#include <SDL2/SDL.h>
#include "menu.h"


static void play_button_response(Game *game) {
    game->state = STATE_PLAY;
}

static void exit_button_response(Game *game) {
    game->running = 0;
}



void menu_reponse(
    InputState *input_state,
    Menu *menu,
    Game *game) {
    SDL_Point mouse = {input_state->mouse.x, input_state->mouse.y};

    if (input_state->mouse.pressed == 1){
        if (SDL_PointInRect(&mouse, &menu->play_button.rect)) {
            play_button_response(game);
        }

        if (SDL_PointInRect(&mouse, &menu->exit_button.rect)) {
            exit_button_response(game);
        }
    }
}
