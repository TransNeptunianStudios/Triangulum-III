#include "triangulum/system/WeaponSystem.h"

namespace triangulum {
namespace system {

WeaponSystem::WeaponSystem(EntityFactory& entity_factory)
: m_entity_factory(entity_factory)
{
}

void WeaponSystem::update(entityx::EntityManager& entities,
                          entityx::EventManager& events,
                          entityx::TimeDelta dt)
{
}

}  // namespace system
}  // namespace triangulum
