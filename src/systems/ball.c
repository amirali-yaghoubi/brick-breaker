#include "ball.h"


static void move_ball(World *world, Game *game) {
    world->ball->position.x += world->ball->velocity.x * game->delta_time;
    world->ball->position.y += world->ball->velocity.y * game->delta_time;
}

static void collide_with_wall(World *world, Game *game) {
    if (world->ball->position.x - world->ball->radius <= 0) {
        world->ball->position.x = world->ball->radius;
        world->ball->velocity.x = - world->ball->velocity.x;
    }
    if (world->ball->position.x + world->ball->radius >= game->size.w) {
        world->ball->position.x = game->size.w - world->ball->radius;
        world->ball->velocity.x = - world->ball->velocity.x;
    }
    if (world->ball->position.y - world->ball->radius <= 0) {
        world->ball->position.y = world->ball->radius;
        world->ball->velocity.y = - world->ball->velocity.y;
    }
}


static void collide_with_paddle(World *world) {
    if (world->ball->position.y + world->ball->radius >= world->paddle->position.y) {
        if (world->ball->position.x >= world->paddle->position.x && world->ball->position.x <= world->paddle->position.x + world->paddle->size.w) {
        world->ball->position.y = world->paddle->position.y - world->ball->radius;
            world->ball->velocity.y = - world->ball->velocity.y;
            float relative_intersect = (world->ball->position.x - world->paddle->position.x) / world->paddle->size.w;
            float angle = (relative_intersect - 0.5f) * 1.5f;
            world->ball->velocity.x = sinf(angle) * world->ball->speed;
            world->ball->velocity.y = -cosf(angle) * world->ball->speed;
        }
    }
}

static void collide_with_bricks(World *world, Game *game) {
   float old_x = world->ball->position.x - world->ball->velocity.x * game->delta_time;
   float old_y = world->ball->position.y - world->ball->velocity.y * game->delta_time;
   for (int i = 0; i < world->bricks->cols * world->bricks->rows; i++) {
       if (world->bricks->members[i].hp <= 0) continue;
       if ((world->ball->position.x + world->ball->radius > world->bricks->members[i].position.x) && (world->ball->position.x - world->ball->radius < world->bricks->members[i].position.x + world->bricks->size.w) && (world->ball->position.y + world->ball->radius > world->bricks->members[i].position.y) && (world->ball->position.y - world->ball->radius < world->bricks->members[i].position.y + world->bricks->size.h)) {
           if (old_y + world->ball->radius <= world->bricks->members[i].position.y) {
            world->ball->velocity.y = - world->ball->velocity.y;
            }
            else if (old_y - world->ball->radius >= world->bricks->members[i].position.y + world->bricks->size.h) {
            world->ball->velocity.y = - world->ball->velocity.y;
            }
            else if (old_x + world->ball->radius <= world->bricks->members[i].position.x) {
            world->ball->velocity.x = - world->ball->velocity.x;
            }
            else if (old_x - world->ball->radius >= world->bricks->members[i].position.x + world->bricks->size.w) {
            world->ball->velocity.x = - world->ball->velocity.x;
            }
            world->bricks->members[i].hp = 0;
            break;
        }
    }
}

void ball_update(World *world, Game *game) {
    move_ball(world, game);
    collide_with_wall(world, game);
    //must be changed later, this is just a temporary placeholder for loss mechanism
    //------
    if (world->ball->position.y + world->ball->radius >= game->size.h) {
        world->ball->position.x = game->size.w / 2;
        world->ball->position.y = game->size.h / 2;
    }
    //------
    collide_with_paddle(world);
    collide_with_bricks(world, game);
}
