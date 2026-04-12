#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "game.hpp"
#include "header.hpp"
#include "render.hpp"

using namespace std;
void render(GameObj& g) {
    SDL_SetRenderDrawColor(g.rend, 255, 255, 255, 255);
    SDL_RenderClear(g.rend);

    for (short i = 0; i < GRID_WIDTH; i++) {
        for (short j = 0; j < GRID_HEIGHT; j++) {
            if (g.cells[i][j].state == ALIVE) {
                SDL_SetRenderDrawColor(g.rend, 0, 0, 0, 255);
            } else if (g.cells[i][j].state == UNDEAD) {
                SDL_SetRenderDrawColor(g.rend, 255, 255, 255, 255);
            } else {
		SDL_SetRenderDrawColor(g.rend, 169, 169, 169, 255);
	    }

	    // Draw Cells
            SDL_Rect cell = {g.cells[i][j].coords.x * GRID_SIZE, g.cells[i][j].coords.y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
            SDL_RenderFillRect(g.rend, &cell);
        }
    }

    SDL_SetRenderDrawColor(g.rend, 0, 0, 0, 255);
    // Draw Grid
    // Vertical Lines
    for ( int i = 0; i < WINDOW_WIDTH; i+=GRID_SIZE) {
	SDL_RenderDrawLine(g.rend,  i,  0,  i, WINDOW_HEIGHT);
    }
    // Horizontal Lines
    for ( int i = 0; i < WINDOW_HEIGHT; i+=GRID_SIZE) {
        SDL_RenderDrawLine(g.rend,  0,  i,  WINDOW_WIDTH, i);
    }


    SDL_RenderPresent(g.rend);
}
