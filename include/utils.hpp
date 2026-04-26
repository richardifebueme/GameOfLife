#pragma once
#include <SDL2/SDL.h>

#include "header.hpp"
#include "game.hpp"

void toggle_game_state(GameObj& g);
SDL_Point get_grid_point(int x, int y);
bool is_valid_point(int x, int y);
int count_live_neighbours(GameObj& g, int x, int y);

void toggle_cell(Cell cells[GRID_WIDTH][GRID_HEIGHT], int x, int y, CellState state);
void update_state(GameObj& g);
void reset_cells(GameObj& g);
