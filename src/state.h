#pragma once

#include "level.h"
#include "graphics.h"

class GameState {
public:
  GameState();
  ~GameState();

  void update(Direction);
  void draw(Graphics*);
};

class PlayState : public GameState {
public:
  PlayState(std::string);
  ~PlayState();

  void update(Direction);
  void draw(Graphics*);
  Level level_;
private:
  int tick_;
  Friend *pacman;
};