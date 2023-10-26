#include <SDL/SDL.h>

// for rendering images and graphics on screen
#include <SDL/SDL_test_images.h>

// for using SDL_Delay() functions
#include <SDL/SDL_timer.h>
#include <iostream>
int main(int argc, char *argv[])
{

  // returns zero on success else non-zero
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << "error initializing SDL: " << SDL_GetError();
  }
  SDL_Window *win = SDL_CreateWindow("GAME",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     1000, 1000, 0);
  while (1)
    ;

  return 0;
}