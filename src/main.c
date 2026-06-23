/*
 * Brick Breaker - SDL2
 * Simple 2D game written in C.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "entities/game.h"
#include "entities/world.h"
#include "entities/bricks.h"

#include "render/render.h"

#include "platform/sdl_init.h"
#include "platform/events.h"

#include "systems/paddle.h"
#include "systems/ball.h"

#include "ui/menu_init.h"
#include "ui/menu.h"



//---------------------------------------
int main() {
    
    //Initialize paramiters
    GameState game_state = STATE_MENU;
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
    bricks.size.w = 74;
    bricks.size.h = 22;
    bricks.cols = 10;
    bricks.rows = 5;

    World world = {
        .ball = &ball,
        .paddle = &paddle,
        .bricks = &bricks
    };

    //Initialize menu
    int play_button_w = (int)(game.size.w * 0.29f);
    int play_button_h = (int)(game.size.h * 0.10f);

    int exit_button_w = play_button_w;
    int exit_button_h = play_button_h;

    int game_result_w = play_button_w;
    int game_result_h = play_button_h;

    SDL_Rect play_button = {
        .x = (game.size.w - play_button_w) / 2,
        .y = ((game.size.h - play_button_h) / 2) - game.size.h * 0.10f,
        .w = play_button_w,
        .h = play_button_h
        };
    SDL_Rect exit_button = {
        .x = (game.size.w - exit_button_w) / 2,
        .y = ((game.size.h - exit_button_h) / 2) + game.size.h * 0.06f,
        .w = exit_button_w,
        .h = exit_button_h
        };
    SDL_Rect game_result = {
        .x = (game.size.w - play_button_w) / 2,
        .y = ((game.size.h - play_button_h) / 2) - game.size.h * 0.30f,
        .w = game_result_w,
        .h = game_result_h
        };

    Menu menu = {
        .background_color = {120, 130, 230, 255},

        .play_button = {
            .rect = play_button,
            .text = (Text){
                .string = "Play",
                .color = {225, 255, 255, 255},
                .texture = NULL
                },
            .background_color = {20, 90, 70, 255}
        },

        .exit_button = {
            .rect = exit_button,
            .text = {
                .string = "Exit",
                .color = {255, 255, 255, 255},
                .texture = NULL
            },
            .background_color = {80, 70, 15, 255}
        },

        .game_result = {
            .rect = game_result,
            .text = {
                .string = ".",
                .color = {0, 0, 0, 0},
                .texture = NULL
            },
            .background_color = {0, 0, 0, 0}
        }
    };


    //Initialize Input State struct
    InputState input_state = {0};

    //Initialize SDL
    if (init_sdl(&game) != 0) return 1;

    if (generate_bricks_array(world.bricks) != 0) {
        fprintf(stderr, "Error in allocating memory!\n");
        cleanup_sdl(&game);
        return 1;
    }

    menu_init(&menu, &game);

    //Main loop
    game.running = 1;
    Uint32 last_time = SDL_GetTicks();
    while (game.running) {

        if (input_state.quit == 1) {
            game.running = 0;
        }

        //Delta time
        Uint32 current_time  = SDL_GetTicks();
        game.delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;
        
        //Get events
        handle_events(&input_state);

        //handle game states
        switch (game.state) {
            case STATE_PLAY:
                //Updating the game
                paddle_update(&world, &game);
                ball_update(&world, &game);
                game.fps = 1.0 / game.delta_time;
                //Render
                render_game(&world, &game);
                break;

            default:
                // To prepare the texts to be rendered(generating textures)
                menu_init(&menu, &game);
                //Update menu
                menu_reponse(&input_state, &menu, &game);
                render_menu(&menu, &game);
                //reset the game bricks
                reset_bricks_hp(world.bricks);
                break;
        }

        //To change the text and color based on tge game state
        switch (game.state) {
            case STATE_MENU:
                menu.game_result.text.string = "Wellcome!";
                menu.game_result.text.color = (SDL_Color){255, 255, 255, 255};
                break;

            case STATE_LOSE:
                menu.game_result.text.string = "You Lose!";
                menu.game_result.text.color = (SDL_Color){255, 0, 0, 255};
                break;

            case STATE_WIN:
                menu.game_result.text.string = "You Won!";
                menu.game_result.text.color = (SDL_Color){0, 255, 0, 255};
                break;
            default:
                break;
        }

        //Fps cap
        Uint32 frame_time = SDL_GetTicks() - current_time;
        if (frame_time < frame_duration_ms) {
            SDL_Delay((Uint32)frame_duration_ms - frame_time);
        }
    }

    //Cleanup
    cleanup_sdl(&game);
    free_bricks(world.bricks);

    return 0;
}
//---------------------------------------
