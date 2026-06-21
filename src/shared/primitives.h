#ifndef PRIMITIVES_H
#define PRIMITIVES_H

typedef struct {
    float x;
    float y;
} Vector2D;

typedef struct {
    float w;
    float h;
} Size2D;

typedef enum {
    STATE_MENU,
    STATE_PLAY,
    STATE_WIN,
    STATE_LOSE
} GameState;

#endif
