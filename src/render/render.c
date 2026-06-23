#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "render.h"


//static functions for the game
static void render_game_background(Game *game) {
    SDL_SetRenderDrawColor(
        game->renderer,
        game->background_color.r,
        game->background_color.g,
        game->background_color.b,
        game->background_color.a
        );

    SDL_RenderClear(game->renderer);
}

static void render_paddle(World *world, Game *game) {
    SDL_Rect paddle = {
        (int)world->paddle->position.x,
        (int)world->paddle->position.y,
        (int)world->paddle->size.w,
        (int)world->paddle->size.h
    };

    SDL_SetRenderDrawColor(
        game->renderer,
        world->paddle->color.r,
        world->paddle->color.g,
        world->paddle->color.b,
        world->paddle->color.a
    );

    SDL_RenderFillRect(game->renderer, &paddle);
}

static void render_ball(World *world, Game *game) {
    filledCircleRGBA(
        game->renderer,
        world->ball->position.x,
        world->ball->position.y,
        world->ball->radius,
        world->ball->color.r,
        world->ball->color.g,
        world->ball->color.b,
        world->ball->color.a
    );
}

static void render_bricks(World *world, Game *game) {
    for (int i = 0; i < world->bricks->cols * world->bricks->rows; i++) {
        if (world->bricks->members[i].hp <= 0) continue;
        SDL_Rect brick = {
            (int)world->bricks->members[i].position.x,
            (int)world->bricks->members[i].position.y,
            (int)world->bricks->size.w,
            (int)world->bricks->size.h
        };

        SDL_SetRenderDrawColor(
            game->renderer,
            world->bricks->members[i].color.r,
            world->bricks->members[i].color.g,
            world->bricks->members[i].color.b,
            world->bricks->members[i].color.a
        );

        SDL_RenderFillRect(game->renderer, &brick);
    }
}



//static functions for the menu
static void render_menu_background(Menu *menu, Game *game) {
    SDL_SetRenderDrawColor(
        game->renderer,
        menu->background_color.r,
        menu->background_color.g,
        menu->background_color.b,
        menu->background_color.a
    );

    SDL_RenderClear(game->renderer);
}

static void render_play_button(Menu *menu, Game *game) {
    SDL_SetRenderDrawColor(
        game->renderer,
        menu->play_button.background_color.r,
        menu->play_button.background_color.g,
        menu->play_button.background_color.b,
        menu->play_button.background_color.a
    );

    SDL_RenderFillRect(game->renderer, &menu->play_button.rect);

    //Text
    SDL_RenderCopy(
        game->renderer,
        menu->play_button.text.texture,
        NULL,
        &menu->play_button.rect
    );
}

static void render_exit_button(Menu *menu, Game *game) {
    SDL_SetRenderDrawColor(
        game->renderer,
        menu->exit_button.background_color.r,
        menu->exit_button.background_color.g,
        menu->exit_button.background_color.b,
        menu->exit_button.background_color.a
    );

    SDL_RenderFillRect(game->renderer, &menu->exit_button.rect);

    //Text
    SDL_RenderCopy(
        game->renderer,
        menu->exit_button.text.texture,
        NULL,
        &menu->exit_button.rect
    );
}

static void render_game_result(Menu *menu, Game *game) {
    SDL_SetRenderDrawColor(
        game->renderer,
        menu->game_result.background_color.r,
        menu->game_result.background_color.g,
        menu->game_result.background_color.b,
        menu->game_result.background_color.a
    );

    SDL_RenderFillRect(game->renderer, &menu->game_result.rect);

    //Text
    SDL_RenderCopy(
        game->renderer,
        menu->game_result.text.texture,
        NULL,
        &menu->game_result.rect
    );
}

//Render game frame pipeline
void render_game(World *world, Game *game) {
    render_game_background(game);

    render_paddle(world, game);

    render_ball(world, game);

    render_bricks(world, game);

    SDL_RenderPresent(game->renderer);
}

//Render menu pipeline
void render_menu(Menu *menu, Game *game) {
    render_menu_background(menu, game);
    render_play_button(menu, game);
    render_exit_button(menu, game);
    render_game_result(menu, game);
    SDL_RenderPresent(game->renderer);
}
