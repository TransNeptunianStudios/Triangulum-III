#ifndef _SYSTEM_EVENTS_H
#define _SYSTEM_EVENTS_H

#include "entityx/Entity.h"

namespace triangulum {

  struct ScoreEvent {
  ScoreEvent(int score, std::string scoreInfo = "") : score(score), scoreInfo(scoreInfo) {}
    int score;
    std::string scoreInfo;

  };

  struct CollisionEvent {
  CollisionEvent(entityx::Entity left, entityx::Entity right) : left(left), right(right) {}
    entityx::Entity left, right;
  };

  struct CreateWorldEvent {
  CreateWorldEvent(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {}
    int sizeX, sizeY;
  };


}  // namespace triangulum

#endif
