#ifndef EVENTS_H
#define EVENTS_H

#include "entities/world.h"
#include "entities/game.h"

typedef struct {
    int quit;

    struct {
        int x, y;
        int down;
        int pressed;
        int released;
    } mouse;
} InputState;

void handle_events(InputState *input_state);

#endif
