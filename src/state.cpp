#include "state.h"

GameState::GameState() {};
GameState::~GameState() {};

void GameState::update(Direction dir) {};
void GameState::draw(Graphics *graphics) {};

PlayState::PlayState(std::string layout) {
  tick_ = 0;
  parseLayoutFromString(layout, &level_.layout);

  pacman = &level_.friends[E_Pacman];
  pacman->type = E_Pacman;

  for (int i = 0; i < 5; i++) {
    Friend *pal = &level_.friends[i];

    pal->type = (Entity)i;

    pal->position.x = 14;
    pal->position.y = 11;

    pal->speed = 1.0;

    pal->dir = Dir_Right;
  }

  pacman->position.x = 13;
  pacman->position.y = 21;
  pacman->speed = 1.5;
};
PlayState::~PlayState() {};

void PlayState::update(Direction desired) {
  // repeating 7 seconds of scatter followed by 20 seconds of chasing
  int lim = 60 * 7 + 60 * 20;

  if (tick_ % lim > 60 * 7) {
    level_.state = STATE_CHASE;
  } else {
    level_.state = STATE_SCATTER;
  }

  updateLevel(&level_, tick_, desired);

  if (level_.state == STATE_DEAD) {
    // quit = true;
    // printf("+-|  GAMEOVER  |--+\n");
    // printf("|                 |\n");
    // printf("|    Score: %i    |\n", level_.score);
    // printf("|                 |\n");
    // printf("+-|------------|--+\n");
  }

  tick_ += 1;
};
void PlayState::draw(Graphics *graphics) {
  graphics->drawLayout(&level_);
};


