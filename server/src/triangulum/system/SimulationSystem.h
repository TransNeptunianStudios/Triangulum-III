#ifndef SIMULATION_SYSTEM_H
#define SIMULATION_SYSTEM_H

#include "Box2D/Dynamics/b2World.h"
#include "entityx/System.h"

namespace triangulum {
namespace system {

class SimulationSystem : public entityx::System<SimulationSystem>,
                         public b2ContactListener
{
public:
  SimulationSystem(entityx::EntityManager& entity_manager, b2World& world);

  void update(entityx::EntityManager& entities,
              entityx::EventManager& events,
              entityx::TimeDelta dt);

  void BeginContact(b2Contact* contact);

  void EndContact(b2Contact* contact);

private:
  entityx::EntityManager& m_entity_manager;

  b2World& m_world;

  int32 m_velocityIterations;

  int32 m_positionIterations;
};

}  // namespace system
}  // namespace triangulum

#endif
