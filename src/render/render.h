#ifndef RENDER_H
#define RENDER_H

#include "entities/world.h"
#include "entities/game.h"
#include "ui/menu.h"

void render_game(World *world, Game *game);
void render_menu(Menu *menu, Game *game);

#endif
