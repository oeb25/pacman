#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <map>
#include "vector2.h"
#include "level.h"
#include "graphics.h"
#include "world.h"
#include "state.h"

int main() {
  srand(time(NULL));

  int score = 0;

  std::stringstream l;

  std::string line;

  std::ifstream file ("map.txt");

  if (file.is_open()) {
    while (std::getline(file, line)) {
      l << line << '\n';
    }

    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
    return 0;
  }

  PlayState state(l.str());
  Direction desired = Dir_Right;

  Graphics graphics;

  bool quit = false;
  SDL_Event event;

  int tick = 0;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_RIGHT:
            desired = Dir_Right;
            break;
          case SDLK_DOWN:
            desired = Dir_Down;
            break;
          case SDLK_LEFT:
            desired = Dir_Left;
            break;
          case SDLK_UP:
            desired = Dir_Up;
            break;
          case SDLK_ESCAPE:
            quit = true;
            break;
        }
      }
    }

    state.update(desired);
    state.draw(&graphics);

    if (state.level_.state == STATE_DEAD) {
      state = *new PlayState(l.str());

    }

    SDL_Delay(16);
  }

  return 0;
};

