#include "level.h"

int sign(int a) {
  return a == 0 ? 0 : abs(a) / a;
}

int min(int a, int b) {
  return a < b ? a : b;
}

void parseLayoutFromString(const std::string str, Layout *layout) {
  int i, x, y;

  x = 0;
  y = 0;

  layout->width = MAX_WIDTH;

  unsigned int len = strlen(str.c_str());

  for (i = 0; i < len; i++) {
    bool skip = false;

    Thing type = T_Empty;

    switch (str[i]) {
      case '#':
        type = T_Wall;
        break;

      case '.':
        // type = T_Empty;
        type = T_Dot;
        break;

      case 'o':
        type = T_Upgrade;
        break;

      case 's':
        type = T_Empty;
        break;

      case '\n':
        if (y == 0) {
          layout->width = i;
        }

        skip = true;

        y += 1;
        break;
    }

    if (!skip) {
      layout->data[i % (layout->width + 1)][y] = type;
    }
  }

  layout->height = y;

  // for (y = 0; y < HEIGHT; y++) {
  //   for (x = 0; x < WIDTH; x++) {
  //     printf("(%i,%i) -> %c\n", x, y, str[x + y * WIDTH]);
  //     switch (str[x + y * WIDTH]) {
  //       case '#':
  //         layout->data[x][y] = T_Wall;
  //         break;
  //       default:
  //         layout->data[x][y] = T_Empty;
  //         break;
  //     }
  //   }
  // }
}
void move(Position *pos, Direction dir) {
  switch (dir) {
    case Dir_Right:
      pos->x += 1;
      break;
    case Dir_Down:
      pos->y += 1;
      break;
    case Dir_Left:
      pos->x -= 1;
      break;
    case Dir_Up:
      pos->y -= 1;
      break;
    default:
      break;
  }
}

int distanceSq(Position *a, Position *b) {
  int dx = a->x - b->x;
  int dy = a->y - b->y;

  return dx * dx + dy * dy;
}

#define NUM_FRIENDS 5;

void updateLevel(Level *level, int tick, Direction desired) {
  Layout *layout = &level->layout;
  int i, n, intersections, dx, dy;
  bool pass;
  int distanceses[4];
  Position next;
  Direction dir;

  Friend *pacman = &level->friends[0];
  Friend *pal;

  for (i = 0; i < 5; i++) {
    pal = &level->friends[i];

    intersections = 0;

    for (n = 0; n < 4; n++) {
      dir = (Direction)(1 << n);

      next.x = pal->position.x;
      next.y = pal->position.y;

      move(&next, dir);

      if (layout->data[next.x][next.y] != T_Wall) {
        intersections += 1;
      }
    }

    /*
    if at intersection then
      if pacman then
        set desired direction if valid
      else
        peform ai -> set target
      end
    else if next position is a wall then
      rotate until a new valid direction is found
    end

    move towards set direction
    */

    if (i == 0 && pal->dir != desired) {
      next.x = pal->position.x;
      next.y = pal->position.y;

      move(&next, desired);

      if (layout->data[next.x][next.y] != T_Wall) {
        pal->dir = desired;
      }
    }

    if (tick % (int)(10 / pal->speed) == 0) {
      pass = false;
      int len = 100000;
      int lenb = 0;
      Direction shortest;

      if (intersections > 2) {
        if (i != 0) {
          // AI
          if (level->state == STATE_SCATTER) {
            switch ((Entity)i) {
              case E_Pacman:
                break;
              case E_Blinky:
                pal->target.x = 28 + 10;
                pal->target.y = 1;
                break;
              case E_Speedy:
                pal->target.x = 1 - 10;
                pal->target.y = 1;
                break;
              case E_Bashful:
                pal->target.x = 27;
                pal->target.y = 28;
                break;
              case E_Pokey:
                pal->target.x = 1;
                pal->target.y = 28;
                break;
            }
          } else {
            switch ((Entity)i) {
              case E_Pacman:
                break;
              case E_Blinky:
                pal->target = pacman->position;
                break;
              case E_Speedy:
                pal->target.x = pacman->position.x;
                pal->target.y = pacman->position.y;

                move(&pal->target, pacman->dir);
                move(&pal->target, pacman->dir);
                move(&pal->target, pacman->dir);
                move(&pal->target, pacman->dir);
                break;
              case E_Bashful:
                pal->target.x = pacman->position.x;
                pal->target.y = pacman->position.y;

                move(&pal->target, pacman->dir);
                move(&pal->target, pacman->dir);

                dx = pal->target.x - level->friends[(int)E_Blinky].position.x;
                dy = pal->target.y - level->friends[(int)E_Blinky].position.y;

                pal->target.x += dx;
                pal->target.y += dy;
                break;
              case E_Pokey:
                pal->target = pal->position;
                move(&pal->target, (Direction)(1 <<rand()));
                break;
            }
          }

          for (n = 0; n < 4; n++) {
            dir = (Direction)(1 << n);

            next.x = pal->position.x;
            next.y = pal->position.y;

            move(&next, dir);

            if (layout->data[next.x][next.y] != T_Wall) {
              lenb = distanceSq(&next, &pal->target);

              if (lenb < len) {
                len = lenb;
                shortest = dir;
              }
            }
          }

          pal->dir = shortest;
          // pass = true;
        }
      }

      if (!pass) {
        next.x = pal->position.x;
        next.y = pal->position.y;

        move(&next, pal->dir);

        if (layout->data[next.x][next.y] == T_Wall) {
          if (i == 0) {
            pal->dir = Dir_None;
          } else {
            for (n = 0; n < 4; n++) {
              dir = (Direction)(1 << n);

              next.x = pal->position.x;
              next.y = pal->position.y;

              move(&next, dir);

              Direction common = (Direction)(dir | pal->dir);

              if (layout->data[next.x][next.y] != T_Wall &&
                common != dir &&
                common != Dir_Vertical &&
                common != Dir_Horizontal) {
                pal->dir = dir;
                break;
              }
            }
          }
        }
      }

      next.x = pal->position.x;
      next.y = pal->position.y;

      move(&next, pal->dir);

      pal->position.x = next.x;
      pal->position.y = next.y;
    }

    if (i != 0 && pal->position.x == pacman->position.x && pal->position.y == pacman->position.y) {
      printf("Final score: %i\n", level->score);
      level->state = STATE_DEAD;
    }

    pal->cur_pos.x = pal->position.x * 10;
    pal->cur_pos.y = pal->position.y * 10;
  }

  if (layout->data[pacman->position.x][pacman->position.y] == T_Dot) {
    level->score += 1;
    layout->data[pacman->position.x][pacman->position.y] = T_Empty;
  }
}