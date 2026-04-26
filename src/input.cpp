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
                case SDLK_h:
                    g.displayGrid = !g.displayGrid;
                    break;
                case SDLK_SPACE:
                    toggle_game_state(g);
                    break;
                case SDLK_r:
                    reset_cells(g);
                    break;
            }
        }

        // Handle mouse button down (start of a drag)
        if (g.event.type == SDL_MOUSEBUTTONDOWN) {
                g.btn = get_grid_point(g.event.button.x, g.event.button.y);
            if (g.event.button.button == SDL_BUTTON_LEFT) {
                // Start dragging
                g.state = GameState::DRAW;
            }
        }

        // Handle mouse motion (dragging)
        if (g.state == GameState::DRAW) {
            g.btn = get_grid_point(g.event.button.x, g.event.button.y);
        }

        // Handle mouse button up (end of drag)
        if (g.event.type == SDL_MOUSEBUTTONUP) {
            // Stop dragging
            g.state = GameState::IDLE;
        }
    }
}
