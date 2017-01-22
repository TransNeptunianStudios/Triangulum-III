#ifndef _WEAPON_H
#define _WEAPON_H

#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct Weapon : public entityx::Component<Weapon>
{
  Weapon();
};

}  // namespace component
}  // namespace triangulum

#endif
