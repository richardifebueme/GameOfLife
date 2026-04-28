#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>

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
            if (is_valid_point(g.btn.x, g.btn.y) && (g.btn.x != g.last_btn.x || g.btn.y != g.last_btn.y)) {
                if (!cell_is_alive(g, g.btn))
                    toggle_cell_state(g.cells, g.btn.x, g.btn.y, ALIVE);
                else
                    toggle_cell_state(g.cells, g.btn.x, g.btn.y, UNDEAD);
            }
            g.last_btn = g.btn;
            break;
    }

    switch (g.cs) {
        case ColorScheme::LIGHT:
            g.background_clr = Color::WHITE;
            g.living_cell_clr = Color::BLACK;
            g.dead_cell_clr = Color::GRAY;
            break;
        case ColorScheme::DARK:
            g.background_clr = Color::BLACK;
            g.living_cell_clr = Color::WHITE;
            g.dead_cell_clr = Color::BLACK;
            break;
    }

    // Set the background color
    setColor(g, g.background_clr);
    SDL_RenderClear(g.rend);

    for (short i = 0; i < GRID_WIDTH; i++) {
        for (short j = 0; j < GRID_HEIGHT; j++) {
            if (g.cells[i][j].state == ALIVE) {
                setColor(g, g.living_cell_clr); // Living cell color
            } else if (g.cells[i][j].state == UNDEAD) {
                setColor(g, g.background_clr); // background-color used for undead cells
            } else {
                setColor(g, g.dead_cell_clr); // dead cell color
	    }

	    // Draw Cells
            SDL_Rect cell = {g.cells[i][j].coords.x * GRID_SIZE, g.cells[i][j].coords.y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
            SDL_RenderFillRect(g.rend, &cell);
        }
    }

    // Draw Grid
    if (g.displayGrid) {
        setColor(g, g.grid_clr);
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
