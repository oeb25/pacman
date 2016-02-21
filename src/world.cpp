#include "world.h"

unsigned int createEntity(World *world) {
  unsigned int entity;

  for (entity = 0; entity < MAX_ENTITES; entity++) {

    // find empty slot for entity to live
    if (world->masks[entity] == COMPONENT_NONE) {
      return entity;
    }
  }

  printf("Error! No more entities in world container!\n");
  return MAX_ENTITES;
};

unsigned int createEntity(World *world, int mask) {
  int id = createEntity(world);

  if (id != MAX_ENTITES) {
    world->masks[id] = mask;
  }

  return id;
};

void deleteEntity(World *world, unsigned int entity) {
  world->masks[entity] = COMPONENT_NONE;
};

void updateMovement(World *world) {
  unsigned int entity;

  for (entity = 0; entity < MAX_ENTITES; entity++) {
    if ((world->masks[entity] & MOVEMENT_MASK) == MOVEMENT_MASK) {
      world->position[entity] += world->velocity[entity];
      // world->velocity[entity] *= 0.8;
    }
  }
}

void renderWorld(World *world, Graphics *graphics) {
  graphics->clear();

  unsigned int entity;

  for (entity = 0; entity < MAX_ENTITES; entity++) {
    if ((world->masks[entity] & DISPLAY_MASK) == DISPLAY_MASK) {
      Vector2 *pos = &world->position[entity];
      SDL_Rect *rect = &world->display[entity];

      rect->x = pos->x;
      rect->y = pos->y;
      rect->w = 10;
      rect->h = 10;
    }

    graphics->fillRects(world->display);
  }

  graphics->flip();
}

void updateWorld(World *world) {
  updateMovement(world);
};
