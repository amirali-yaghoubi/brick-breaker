#include "bricks.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

int generate_bricks_array(Bricks *bricks) {
    Brick *bricks_arr = malloc(bricks->cols * bricks->rows * sizeof(Brick));
    if (bricks_arr == NULL) {
        return 1;
    }
    bricks->members = bricks_arr;
    for (int i = 0; i < bricks->cols * bricks->rows; i++) {
        int row = i / bricks->cols;
        int col = i % bricks->cols;
        float x = (col + 1) * bricks->padding.x + col * bricks->size.w;
        float y = (row + 1) * bricks->padding.y + row * bricks->size.h; 
        bricks_arr[i] = (Brick){
            .position = {
                .x = x,
                .y = y
            },
            .hp = 1,
            .color = {
                255,
                255,
                255,
                255
            }
        };
    }
    return 0;
}

void free_bricks(Bricks *bricks) {
    free(bricks->members);
    bricks->members = NULL;
}

void reset_bricks_hp(Bricks *bricks) {
    for (int i = 0; i < bricks->cols * bricks->rows; i++) {
        bricks->members[i].hp = 1;
    }
}
