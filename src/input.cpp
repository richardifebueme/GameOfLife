#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>
#include "input.hpp"
#include "utils.hpp"

using namespace std;

void handle_input(GameObj& g) {
    bool is_dragging = false; // Track if the mouse button is pressed

    while (SDL_PollEvent(&g.event)) {
        // Handle keyboard events
        if (g.event.type == SDL_KEYDOWN) {
            switch (g.event.key.keysym.sym) {
                case SDLK_q:
                    g.isRunning = false;
                    break;
                case SDLK_SPACE:
                    update_state(g);
                    break;
                case SDLK_r:
                    reset_cells(g);
                    break;
            }
        }

        // Handle mouse button down (start of a drag)
        if (g.event.type == SDL_MOUSEBUTTONDOWN) {
            if (g.event.button.button == SDL_BUTTON_LEFT) {
                // Start dragging
                is_dragging = true;

                // Toggle the cell at the initial mouse position
                SDL_Point btn = get_grid_point(g.event.button.x, g.event.button.y);
                if (btn.x >= 0 && btn.x < GRID_WIDTH && btn.y >= 0 && btn.y < GRID_HEIGHT) {
                    toggle_cell(g.cells, btn.x, btn.y);
                }
            }
        }

        // Handle mouse motion (dragging)
        if (g.event.type == SDL_MOUSEMOTION && is_dragging) {
            SDL_Point btn = get_grid_point(g.event.motion.x, g.event.motion.y);
            if (btn.x >= 0 && btn.x < GRID_WIDTH && btn.y >= 0 && btn.y < GRID_HEIGHT) {
                toggle_cell(g.cells, btn.x, btn.y);
            }
        }

        // Handle mouse button up (end of the drag)
        if (g.event.type == SDL_MOUSEBUTTONUP) {
            if (g.event.button.button == SDL_BUTTON_LEFT) {
                // Stop dragging
                is_dragging = false;
            }
        }
    }
}
