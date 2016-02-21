#include "graphics.h"

Graphics::Graphics() {
  SDL_CreateWindowAndRenderer(640, 480, 0, &window_, &renderer_);
}
Graphics::~Graphics() {
  SDL_Quit();
}

void Graphics::clear() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
}

void Graphics::fillRect(const SDL_Rect *rect) {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer_, rect);
}

void Graphics::fillRects(const SDL_Rect rects[]) {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
  SDL_RenderFillRects(renderer_, rects, 100);
}

void Graphics::drawLayout(Level *level) {
  Layout *layout = &level->layout;

  int size = 10;

  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = size - 2;
  rect.h = size - 2;

  this->clear();

  for (int y = 0; y < layout->height; y++) {
    for (int x = 0; x < layout->width; x++) {
      rect.x = x * size + 2;
      rect.y = y * size + 2;
      rect.w = size - 4;
      rect.h = size - 4;

      switch (layout->data[x][y]) {
        case T_Empty:
          SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
          break;
        case T_Wall:
          rect.x = x * size;
          rect.y = y * size;
          rect.w = size;
          rect.h = size;
          SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
          break;
        case T_Dot:
          rect.x = x * size + 4;
          rect.y = y * size + 4;
          rect.w = size - 8;
          rect.h = size - 8;
          SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
          break;
        case T_Upgrade:
          SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
          break;
      }

      SDL_RenderFillRect(renderer_, &rect);
    }
  }

  rect.w = 8;
  rect.h = 8;

  for (int i = 0; i < 5; i++) {
    Friend *f = &level->friends[i];

    rect.x = f->cur_pos.x + 1;
    rect.y = f->cur_pos.y + 1;

    switch (f->type) {
      case E_Pacman:
        SDL_SetRenderDrawColor(renderer_, 255, 255, 0, 255);
        break;
      case E_Blinky:
        SDL_SetRenderDrawColor(renderer_, 255, 95, 95, 255);
        break;
      case E_Speedy:
        SDL_SetRenderDrawColor(renderer_, 255, 184, 255, 255);
        break;
      case E_Bashful:
        SDL_SetRenderDrawColor(renderer_, 1, 255, 255, 255);
        break;
      case E_Pokey:
        SDL_SetRenderDrawColor(renderer_, 255, 185, 81, 255);
        break;
    }

    SDL_RenderFillRect(renderer_, &rect);
  }

  this->flip();
}

void Graphics::flip() {
  SDL_RenderPresent(renderer_);
}