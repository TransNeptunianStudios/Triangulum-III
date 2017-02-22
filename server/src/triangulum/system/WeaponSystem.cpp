#include "triangulum/system/WeaponSystem.h"

#include "triangulum/EntityFactory.h"
#include "triangulum/component/Bullet.h"
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
  entities.each<Bullet>([&dt](
  Entity entity, Bullet& bullet) {
    bullet.age += dt;

    if (bullet.age > bullet.life_time)
    {
      entity.destroy();
    }
  });

  entities.each<DynamicBody, Input, Weapon>([this, &entities, &dt](
  Entity entity, DynamicBody& body, Input& input, Weapon& weapon) {

    weapon.shoot_timer -= dt;

    if (input.fire && weapon.shoot_timer <= 0.0)
    {
      m_entity_factory.create_bullet(entities.create(),
                                     entity.id(),
                                     body.get_position(),
                                     body.get_linear_velocity(),
                                     body.get_rotation());

      weapon.shoot_timer = 0.5;
    }
  });
}

}  // namespace system
}  // namespace triangulum
