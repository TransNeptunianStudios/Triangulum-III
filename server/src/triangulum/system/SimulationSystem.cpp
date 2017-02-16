#include "triangulum/system/SimulationSystem.h"

#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "triangulum/component/Damage.h"
#include "triangulum/component/Health.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;

SimulationSystem::SimulationSystem(EntityManager& entity_manager,
                                   b2World& world)
: m_entity_manager(entity_manager)
, m_world(world)
, m_velocityIterations(8)  // how strongly to correct velocity
, m_positionIterations(3)  // how strongly to correct position
{
  world.SetContactListener(this);
}

void SimulationSystem::update(EntityManager& entities,
                              EventManager& events,
                              TimeDelta dt)
{
  m_world.Step(dt, m_velocityIterations, m_positionIterations);

  entities.each<Health>([](Entity entity, Health& health) {
    if (health.health <= 0.0)
    {
      entity.destroy();
    }
  });
}

void SimulationSystem::BeginContact(b2Contact* contact)
{
  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

  if (!bodyUserData)
  {
    return;
  }

  auto entity_a = m_entity_manager.get(*static_cast<Entity::Id*>(bodyUserData));

  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

  if (!bodyUserData)
  {
    return;
  }

  auto entity_b = m_entity_manager.get(*static_cast<Entity::Id*>(bodyUserData));

  auto health_a = entity_a.component<Health>();

  auto damage_a = entity_a.component<Damage>();

  auto health_b = entity_b.component<Health>();

  auto damage_b = entity_b.component<Damage>();

  if (health_a && damage_b)
  {
    health_a->health -= damage_b->damage;
  }

  if (health_b && damage_a)
  {
    health_b->health -= damage_a->damage;
  }
}

void SimulationSystem::EndContact(b2Contact* contact)
{
}

}  // namespace system
}  // namespace triangulum
