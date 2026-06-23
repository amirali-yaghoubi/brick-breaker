#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "entities/game.h"
#include "platform/events.h"


typedef struct {
    SDL_Color color;
    char *string;
    SDL_Texture *texture;
} Text;

//Label and Button are identical, but they are ready for upgrades in future
typedef struct {
    Text text;
    SDL_Color background_color;
    SDL_Rect rect;
} Label;

typedef struct {
    Text text;
    SDL_Color background_color;
    SDL_Rect rect;
    int xxx;
} Button;

typedef struct {
    SDL_Color background_color;
    Button play_button;
    Button exit_button;
    Label game_result;
    TTF_Font *font;
} Menu;

void menu_reponse(
    InputState *input_state,
    Menu *menu,
    Game *game);

void update_game_result(Menu *menu, Game *game);

#endif
