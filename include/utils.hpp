#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "header.hpp"
#include "game.hpp"

SDL_Point get_grid_point(int x, int y);
int count_live_neighbours(GameObj& g, int x, int y);
void toggle_cell(Cell cells[GRID_WIDTH][GRID_HEIGHT], int x, int y);
void update_state(GameObj& g);
void reset_cells(GameObj& g);
