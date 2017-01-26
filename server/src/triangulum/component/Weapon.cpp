#include "triangulum/component/Weapon.h"

namespace triangulum {
namespace component {

Weapon::Weapon()
: heat(0.0)
, cooldown_time(10.0)
, shoot_timer(0.0)
{
}

}  // namespace component
}  // namespace triangulum
