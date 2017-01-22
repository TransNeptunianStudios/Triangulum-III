#ifndef _GUN_SYSTEM_H
#define _GUN_SYSTEM_H

#include "entityx/System.h"
#include "triangulum/EntityFactory.h"

namespace triangulum {
namespace system {

class WeaponSystem : public entityx::System<WeaponSystem>
{
public:
  WeaponSystem(EntityFactory &entity_factory);

  void update(entityx::EntityManager &entities,
              entityx::EventManager &events,
              entityx::TimeDelta dt);

private:
  EntityFactory m_entity_factory;
};

}  // namespace system
}  // namespace triangulum

#endif
