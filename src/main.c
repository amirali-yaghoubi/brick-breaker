/*
 * Brick Breaker - SDL2
 * Simple 2D game written in C.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "entities/game.h"
#include "entities/world.h"
#include "entities/bricks.h"
#include "render/render.h"
#include "platform/sdl_init.h"
#include "platform/events.h"
#include "systems/paddle.h"
#include "systems/ball.h"



//---------------------------------------
//---------------------------------------
//Main
int main() {
    
    //Initialize paramiters
    GameState game_state;
    Game game = {
        .size = {.w = 800, .h = 600},
        .fps = 60,
        .running = 0,
        .state = game_state,
        .background_color = {64, 64, 64, 255}
    };
    float frame_duration_ms = 1000.0 / game.fps;

    Ball ball = {
        .position = {.x = game.size.w / 2, .y = game.size.h / 3},
        .speed = game.size.w / 1.25,
        .radius = game.size.w / 80,
        .color = {90, 230, 170, 255}
    };
    ball.velocity.x = 0.0;
    ball.velocity.y = ball.speed;

    Paddle paddle = {
        .position = {.x = game.size.w / 2, game.size.h / 1.1},
        .size = {game.size.w / 6, game.size.h / 48},
        .color = {255, 215, 10, 255}
    };

    Bricks bricks;
    bricks.padding.x = 5;
    bricks.padding.y = 5;
    bricks.size.w = 200;
    bricks.size.h = 90;
    bricks.cols = 2;
    bricks.rows = 2;

    World world = {
        .ball = &ball,
        .paddle = &paddle,
        .bricks = &bricks
    };

    //Initialize SDL
    if (init_sdl(&game) != 0) return 1;

    if (generate_bricks_array(world.bricks) != 0) {
        fprintf(stderr, "Error in allocating memory!\n");
        cleanup_sdl(&game);
        return 1;
    }

    //Main loop
    game.running = 1;
    Uint32 last_time = SDL_GetTicks();
    while (game.running) {
        Uint32 current_time  = SDL_GetTicks();
        game.delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        
        //Event loop
        handle_events(&world, &game);

        //Updating the game
        paddle_update(&world, &game);
        ball_update(&world, &game);
        game.fps = 1.0 / game.delta_time;

        //printf("state: %d\n", game.state);

        //Rendering everything
        render(&world, &game);

        Uint32 frame_time = SDL_GetTicks() - current_time;
        if (frame_time < frame_duration_ms) {
            SDL_Delay((Uint32)frame_duration_ms - frame_time);
        }
    }

    cleanup_sdl(&game);
    free_bricks(world.bricks);

    return 0;
}
//---------------------------------------
