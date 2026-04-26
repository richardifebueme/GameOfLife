#pragma once

#include "game.hpp"
#include "types.hpp"

#include <SDL2/SDL.h>

void render(GameObj& g);
void setColor(GameObj& g, Color color);
void draw_cell(GameObj& g, SDL_Point pt);
