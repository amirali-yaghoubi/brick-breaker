#include "menu_init.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>


static SDL_Texture* create_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());  
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(surface);

    return texture;
}



int menu_init(Menu *menu, Game *game) {
    menu->font = TTF_OpenFont("assets/fonts/DejaVuSans.ttf", 18);
    if (!menu->font) {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        return 1;
    }

    menu->play_button.text.texture = create_text(
            game->renderer,
            menu->font,
            menu->play_button.text.string,
            menu->play_button.text.color
        );

    if (!menu->play_button.text.texture) {
        TTF_CloseFont(menu->font);
        return 1;
    }


    menu->exit_button.text.texture = create_text(
            game->renderer,
            menu->font,
            menu->exit_button.text.string,
            menu->exit_button.text.color
        );

    if (!menu->exit_button.text.texture) {
        SDL_DestroyTexture(menu->play_button.text.texture);
        TTF_CloseFont(menu->font);
        return 1;
    }

    menu->game_result.text.texture = create_text(
            game->renderer,
            menu->font,
            menu->game_result.text.string,
            menu->game_result.text.color
        );
    
    if (!menu->game_result.text.texture) {
        SDL_DestroyTexture(menu->play_button.text.texture);
        SDL_DestroyTexture(menu->exit_button.text.texture);
        TTF_CloseFont(menu->font);
        return 1;
    }

    return 0;
}


