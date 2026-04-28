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
    GameState state = GameState::IDLE;
    bool isRunning = false;
    bool displayGrid = true;
    Cell cells[GRID_WIDTH][GRID_HEIGHT];
    SDL_Point btn = {-1, -1};
    SDL_Point last_btn = {-1, -1};
    Color background_clr = Color::WHITE;
    Color living_cell_clr = Color::BLACK;
    Color dead_cell_clr = Color::GRAY;
    Color grid_clr = Color::LIGHT_GRAY;
    ColorScheme cs = ColorScheme::LIGHT;
};

int init_game(GameObj& g);
void destroy_game(GameObj& g);
