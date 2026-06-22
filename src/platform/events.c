#include "events.h"
#include <SDL2/SDL.h>



void handle_events(InputState *input_state) {
    SDL_Event event;

    // reset frame-based flags
    input_state->mouse.pressed = 0;
    input_state->mouse.released = 0;
    input_state->quit = 0;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                input_state->quit = 1;
                break;

            case SDL_MOUSEMOTION:
                input_state->mouse.x = event.motion.x;
                input_state->mouse.y = event.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    input_state->mouse.down = 1;
                    input_state->mouse.pressed = 1;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    input_state->mouse.down = 0;
                    input_state->mouse.released = 1;
                }
                break;
        }
    }
}
