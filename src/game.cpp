#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

#include "header.hpp"
#include "game.hpp"

using namespace std;

int init_game(GameObj& g) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init() failed. Error: " << SDL_GetError() << endl;
        return 1;
    }

    g.win = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (g.win == nullptr) {
        cout << "SDL_CreateWindow() failed. Error: " << SDL_GetError() << endl;
        return 2;
    }

    g.rend = SDL_CreateRenderer(g.win, -1, SDL_RENDERER_ACCELERATED);
    if (g.rend == nullptr) {
        cout << "SDL_CreateRenderer() failed. Error: " << SDL_GetError() << endl;
        return 3;
    }

    // Populate cells
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            g.cells[i][j].coords = SDL_Point{i, j};
        }
    }

    g.isRunning = true;
    return 0;
}

void destroy_game(GameObj& g) {
    SDL_DestroyRenderer(g.rend);
    SDL_DestroyWindow(g.win);
    SDL_Quit();
}
