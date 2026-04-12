#pragma once

#include "game.hpp"

#include <SDL2/SDL.h>

void render(GameObj& g);
void draw_cell(GameObj& g, SDL_Point pt);
