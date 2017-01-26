#ifndef _BULLET_H
#define _BULLET_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Bullet : public entityx::Component<Bullet>
{
  Bullet();

  Bullet(entityx::Entity::Id ownerId_, long damage_, double life_time_);

  entityx::Entity::Id owner_id;

  long damage;

  double life_time;

  double age;

  double produced_heat;
};

}  // namespace component
}  // namespace triangulum

#endif
