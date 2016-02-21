#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#define MAX_WIDTH  200
#define MAX_HEIGHT 200

int sign(int);
int min(int, int);

typedef enum {
  T_Empty,   // ' '
  T_Wall,    // '#'
  T_Dot,     // '.'
  T_Upgrade, // 'o'
} Thing;

typedef enum {
  E_Pacman,
  E_Blinky,
  E_Speedy,
  E_Bashful,
  E_Pokey,
} Entity;

typedef struct {
  Thing data[MAX_WIDTH][MAX_HEIGHT];
  int width;
  int height;

  bool intersections[MAX_WIDTH][MAX_HEIGHT];
} Layout;

typedef enum {
  S_Alive,
  S_Dead,
  S_Afraid,
} State;

typedef struct {
  int x, y;
} Position;

typedef enum {
  Dir_None  = 0,
  Dir_Right = 1 << 0,
  Dir_Down  = 1 << 1,
  Dir_Left  = 1 << 2,
  Dir_Up    = 1 << 3,
  Dir_Horizontal = (Dir_Right | Dir_Left),
  Dir_Vertical   = (Dir_Down  | Dir_Up),
} Direction;

typedef struct {
  Entity type;
  Position position;
  Position cur_pos;

  Position target;

  float speed;
  Direction dir;
  State state;
} Friend;

typedef enum {
  STATE_SCATTER,
  STATE_CHASE,
  STATE_DEAD,
} LevelState;

typedef struct {
  int score;
  Layout layout;
  Friend friends[5];
  LevelState state;
} Level;

void move(Position *pos, Direction dir);
int distanceSq(Position *a, Position *b);

void parseLayoutFromString(const std::string str, Layout *layout);
void updateLevel(Level *level, int tick, Direction desired);