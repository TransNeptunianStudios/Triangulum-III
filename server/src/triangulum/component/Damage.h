#ifndef _DAMAGE_H
#define _DAMAGE_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Damage : public entityx::Component<Damage>
{
  Damage();

  Damage(float damage_);

  float damage;
};

}  // namespace component
}  // namespace triangulum

#endif
