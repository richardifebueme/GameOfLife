#pragma once
#include <SDL2/SDL.h>

#include "header.hpp"
#include "types.hpp"

enum CellState{
    UNDEAD,
    ALIVE,
    DEAD
};

struct Cell {
    CellState state = UNDEAD;
    SDL_Point coords;
};

struct GameObj {
    SDL_Window* win;
    SDL_Renderer* rend;
    SDL_Event event;
    GameState state;
    bool isRunning = false;
    Cell cells[GRID_WIDTH][GRID_HEIGHT];
    SDL_Point btn = {-1, -1};
};

int init_game(GameObj& g);
void destroy_game(GameObj& g);
