#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  SDL_Window *window{nullptr};
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not be initialized.\n";
  } else {
    std::cout << "SDL Video System is ready to go.\n";
  }
  // create window

  window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600, 0);

  SDL_Renderer *renderer{nullptr};
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  bool gameIsRunning = true;
  while (gameIsRunning) {

    SDL_Event event;


    while (SDL_PollEvent(&event)) {
      const Uint8 *state{SDL_GetKeyboardState(NULL)};
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        gameIsRunning = false;
        std::cout << "Escaped key pressed.\n";
      }
    }
  }
  return 0;
}
