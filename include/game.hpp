#pragma once
#include <SDL2/SDL.h>

#include "header.hpp"

enum CellState{
    ALIVE,
    DEAD
};

struct Cell {
    CellState state = DEAD;
    SDL_Point coords;
};

struct GameObj {
    SDL_Window* win;
    SDL_Renderer* rend;
    SDL_Event event;
    bool isRunning = false;
    Cell cells[GRID_WIDTH][GRID_HEIGHT];
};

int init_game(GameObj& g);
void destroy_game(GameObj& g);
