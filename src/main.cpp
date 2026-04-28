#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "game.hpp"
#include "input.hpp"
#include "render.hpp"

using namespace std;
int main() {
    // Create game object
    GameObj game;

    // initialize SDL and game struct
    if (init_game(game) != 0) {
        cout << "init_game() failed" << endl;
    }

    // Gameloop
    while(game.isRunning) {
        handle_input(game);
        render(game);

        SDL_Delay(30);
    }

    destroy_game(game);
}
