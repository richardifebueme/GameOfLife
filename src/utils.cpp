#include <SDL2/SDL.h>
#include <vector>

#include "utils.hpp"
#include "header.hpp"

void toggle_game_state(GameObj& g) {
    if (g.state == GameState::IDLE)
        g.state = GameState::PLAY;
    else g.state = GameState::IDLE;
}

SDL_Point get_grid_point(int x, int y) {
    return SDL_Point {
        x / GRID_SIZE,
        y / GRID_SIZE,
    };
}

int count_live_neighbors(GameObj& g, int x, int y) {
    int count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int nx = x + i;
            int ny = y + j;

            if (nx < 0 || ny < 0 || nx >= GRID_WIDTH || ny >= GRID_HEIGHT)
                continue;

            if (g.cells[nx][ny].state == ALIVE)
                count++;
        }
    }

    return count;
}

void toggle_cell(Cell cells[GRID_WIDTH][GRID_HEIGHT], int x, int y) {
	cells[x][y].state = (cells[x][y].state == ALIVE) ? DEAD : ALIVE;
}


void update_state(GameObj& g) {
	Cell cells_copy[GRID_WIDTH][GRID_HEIGHT];
	for (int i = 0; i < GRID_WIDTH; i++)
		for (int j = 0; j < GRID_HEIGHT; j++)
			cells_copy[i][j].state = g.cells[i][j].state;

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {

			int count = count_live_neighbors(g, i, j);

			if (count < 2 && g.cells[i][j].state == ALIVE) { toggle_cell(cells_copy, i, j); } 

			else if ((count == 2 || count == 3) && g.cells[i][j].state == ALIVE) { continue; } 

			else if (count == 3 && (g.cells[i][j].state == DEAD || g.cells[i][j].state == UNDEAD))
				{ toggle_cell(cells_copy, i, j); } 

			else if (count > 3 && g.cells[i][j].state == ALIVE) { toggle_cell(cells_copy, i, j); }
		}
	}

	for (int i = 0; i < GRID_WIDTH; i++)
		for (int j = 0; j < GRID_HEIGHT; j++)
			g.cells[i][j].state = cells_copy[i][j].state;
}

void reset_cells(GameObj& g) {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for ( int j = 0; j < GRID_HEIGHT; j++) {
			g.cells[i][j].state = UNDEAD;
		}
	}
}
