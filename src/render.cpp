#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "game.hpp"
#include "header.hpp"
#include "utils.hpp"
#include "render.hpp"

using namespace std;

void setColor(GameObj& g, Color color) {
    switch (color) {
    case Color::WHITE:
        SDL_SetRenderDrawColor(g.rend, 255, 255, 255, 255);
        break;
    case Color::BLACK:
        SDL_SetRenderDrawColor(g.rend, 0, 0, 0, 255);
        break;
    case Color::GRAY:
        SDL_SetRenderDrawColor(g.rend, 169, 169, 169, 255);
        break;
    case Color::LIGHT_GRAY:
        SDL_SetRenderDrawColor(g.rend, 108, 108, 108, 255);
        break;

    }
}

void render(GameObj& g) {
    switch(g.state) {
    case GameState::IDLE:
        break;
    case GameState::PLAY:
        update_state(g);
        break;
    case GameState::DRAW:
        // Toggle the cell at the current mouse position
        if (is_valid_point(g.btn.x, g.btn.y)) {
            if (cell_is_alive(g, get_grid_point(g.btn.x, g.btn.y)))
                toggle_cell(g.cells, g.btn.x, g.btn.y, UNDEAD);
            else toggle_cell(g.cells, g.btn.x, g.btn.y, ALIVE);
        }
      break;
    }
    setColor(g, Color::WHITE);
    SDL_RenderClear(g.rend);

    for (short i = 0; i < GRID_WIDTH; i++) {
        for (short j = 0; j < GRID_HEIGHT; j++) {
            if (g.cells[i][j].state == ALIVE) {
                setColor(g, Color::BLACK);
            } else if (g.cells[i][j].state == UNDEAD) {
                setColor(g, Color::WHITE);
            } else {
                setColor(g, Color::GRAY);
	    }

	    // Draw Cells
            SDL_Rect cell = {g.cells[i][j].coords.x * GRID_SIZE, g.cells[i][j].coords.y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
            SDL_RenderFillRect(g.rend, &cell);
        }
    }

    // Draw Grid
    if (g.displayGrid) {
        setColor(g, Color::LIGHT_GRAY);
        // Vertical Lines
        for ( int i = 0; i < WINDOW_WIDTH; i+=GRID_SIZE) {
        SDL_RenderDrawLine(g.rend,  i,  0,  i, WINDOW_HEIGHT);
        }
        // Horizontal Lines
        for ( int i = 0; i < WINDOW_HEIGHT; i+=GRID_SIZE) {
            SDL_RenderDrawLine(g.rend,  0,  i,  WINDOW_WIDTH, i);
        }
    }


    SDL_RenderPresent(g.rend);
}
