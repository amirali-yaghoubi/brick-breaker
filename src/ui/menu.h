#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "entities/game.h"
#include "platform/events.h"


typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    char *text;
    SDL_Color text_color;
    SDL_Texture *texture;
} Button;

typedef struct {
    SDL_Color background_color;
    Button play_button;
    Button exit_button;
    TTF_Font *font;
} Menu;

void menu_reponse(
    InputState *input_state,
    Menu *menu,
    Game *game);

#endif
