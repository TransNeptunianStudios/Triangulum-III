#include "triangulum/system/WeaponSystem.h"

#include "triangulum/EntityFactory.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Input.h"
#include "triangulum/component/Weapon.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;

WeaponSystem::WeaponSystem(EntityFactory& entity_factory)
: m_entity_factory(entity_factory)
{
}

void WeaponSystem::update(entityx::EntityManager& entities,
                          entityx::EventManager& events,
                          entityx::TimeDelta dt)
{
  entities.each<DynamicBody, Input, Weapon>([this, &entities, &dt](
  Entity entity, DynamicBody& body, Input& input, Weapon& weapon) {

    weapon.shoot_timer -= dt;

    if (input.fire && weapon.shoot_timer <= 0.0)
    {
      m_entity_factory.create_bullet(
      entities.create(), body.get_position(), body.get_rotation());

      weapon.shoot_timer = 1.0;
    }
  });
}

}  // namespace system
}  // namespace triangulum
