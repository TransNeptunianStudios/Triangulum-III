#include "triangulum/component/Bullet.h"

using namespace entityx;

namespace triangulum {
namespace component {

Bullet::Bullet()
: owner_id(Entity::INVALID)
, damage(0)
, life_time(0.0)
, age(0.0)
, produced_heat(0.0) // TODO: Not used yet
{
}

Bullet::Bullet(entityx::Entity::Id owner_id_, long damage_, double life_time_)
: owner_id(owner_id_)
, damage(damage_)
, life_time(life_time_)
, age(0.0)
, produced_heat(0.0) // TODO: Not used yet
{
}

}  // namespace component
}  // namespace triangulum
