#pragma once

#include <SDL.h>
#include "vector2.h"
#include "graphics.h"

#define MAX_ENTITES 100

typedef enum {
  COMPONENT_NONE = 0,
  COMPONENT_POSITION = 1 << 0,
  COMPONENT_VELOCITY = 1 << 1,
  COMPONENT_DISPLAY = 1 << 2,
} Component;

// typedef Vector2 Position;
typedef Vector2 Velocity;

#define MOVEMENT_MASK (COMPONENT_POSITION | COMPONENT_VELOCITY)
#define DISPLAY_MASK (COMPONENT_POSITION | COMPONENT_DISPLAY)

typedef struct {
  int masks[MAX_ENTITES];

  Vector2 position[MAX_ENTITES];
  Velocity velocity[MAX_ENTITES];

  SDL_Rect display[MAX_ENTITES];
} World;

unsigned int createEntity(World *world);
unsigned int createEntity(World *world, int mask);

void deleteEntity(World *world, unsigned int entity);

void updateMovement(World *world);

void renderWorld(World *world, Graphics *graphics);

void updateWorld(World *world);