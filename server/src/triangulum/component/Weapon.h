#ifndef _WEAPON_H
#define _WEAPON_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Weapon : public entityx::Component<Weapon>
{
  Weapon();

  double heat;

  double cooldown_time;

  double shoot_timer;
};

}  // namespace component
}  // namespace triangulum

#endif
