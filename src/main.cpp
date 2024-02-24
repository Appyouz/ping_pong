#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_render.h>
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

  // create surface
  SDL_Surface *ballSurface{IMG_Load("../images/ball.png")};
  SDL_Surface *paddleSurface{IMG_Load("../images/paddle.png")};

  // create texture
  SDL_Texture *ballTexture{SDL_CreateTextureFromSurface(renderer, ballSurface)};
  SDL_Texture *paddleTexture{
      SDL_CreateTextureFromSurface(renderer, paddleSurface)};

  SDL_FreeSurface(ballSurface);
  SDL_FreeSurface(paddleSurface);

  // Create rectangle
  SDL_Rect ball{};
  ball.x = 800 / 2;
  ball.y = 600 / 2;
  ball.w = 20;
  ball.h = 20;

  SDL_Rect leftPaddle{};
  leftPaddle.x = 5;
  leftPaddle.y = (600 - 100) / 2;
  leftPaddle.w = 20;
  leftPaddle.h = 100;

  SDL_Rect rightPaddle{};
  rightPaddle.x = 800 - leftPaddle.x - leftPaddle.w;
  rightPaddle.y = (600 - 100) / 2;
  rightPaddle.w = 20;
  rightPaddle.h = 100;
  bool gameIsRunning = true;

  float ballSpeedX = 5.0f; // Set the initial speed of the ball
  float ballSpeedY = 5.0f;
  while (gameIsRunning) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      const Uint8 *state{SDL_GetKeyboardState(NULL)};
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        gameIsRunning = false;
        std::cout << "Escaped key pressed.\n";
      }
      if (state[SDL_SCANCODE_UP]) {
        std::cout << "Up arrow key was pressed.\n";
        if (rightPaddle.y >= 0) {
          rightPaddle.y -= 55;
        }
      } else if (state[SDL_SCANCODE_DOWN]) {
        std::cout << "Down arrow key was pressed.\n";
        if (rightPaddle.y + rightPaddle.h <= 600)
          rightPaddle.y += 55;
      }

      if (state[SDL_SCANCODE_W]) {
        std::cout << "Up arrow key was pressed.\n";
        if (leftPaddle.y >= 0) {
          leftPaddle.y -= 55;
        }
      } else if (state[SDL_SCANCODE_S]) {
        std::cout << "Down arrow key was pressed.\n";
        if (leftPaddle.y + leftPaddle.h <= 600)
          leftPaddle.y += 55;
      }
    }

    // Update ball position
    ball.x += ballSpeedX;
    ball.y += ballSpeedY;
    // Check for collisions with window edges
    if (ball.y <= 0 || ball.y >= (600 - ball.h)) {
      // ballSpeedY = -ballSpeedY; // Reverse Y direction upon collision with
      // top
      ballSpeedY *= -1;
      // or bottom edge
    }
    // Check for collisions with left and right edges
    if (ball.x <= 0 || ball.x >= (800 - ball.w)) {
      ballSpeedX *= -1;
      // ballSpeedX = -ballSpeedX; // Reverse X direction upon collision with
      // left or right edge
    }
    // Check for collisions with paddles
    if (SDL_HasIntersection(&ball, &leftPaddle) ||
        SDL_HasIntersection(&ball, &rightPaddle)) {
      ballSpeedX = -ballSpeedX;
    } 
      // This particular section kind of make ball movement weird other than cool
      // TODO: Fix this
    else if (ball.y <= leftPaddle.y + leftPaddle.h &&
               ball.y + ball.h >= leftPaddle.y) {
      ballSpeedY = -ballSpeedY; // Reverse ball's vertical direction for left
                                // paddle collision
    } else if (ball.y <= rightPaddle.y + rightPaddle.h &&
               ball.y + ball.h >= rightPaddle.y) {
      ballSpeedY = -ballSpeedY; // Reverse ball's vertical direction for right
                                // paddle collision
    }

    SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0xBB, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderCopy(renderer, paddleTexture, NULL, &leftPaddle);
    SDL_RenderCopy(renderer, paddleTexture, NULL, &rightPaddle);

    SDL_RenderCopy(renderer, ballTexture, NULL, &ball);
    SDL_RenderPresent(renderer); // Present the frame
    SDL_Delay(10);               // Delay for 10 milliseconds (adjust as needed)
  }

  // Cleanup
  //
  SDL_DestroyTexture(ballTexture);
  SDL_DestroyTexture(paddleTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
