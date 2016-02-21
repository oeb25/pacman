#pragma once

#include <SDL.h>
#include "level.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

class Graphics{
public:
  Graphics();
  ~Graphics();

  void clear();

  void fillRect(const SDL_Rect *rect);
  void fillRects(const SDL_Rect rect[]);

  void drawLayout(Level*);

  void flip();
private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};