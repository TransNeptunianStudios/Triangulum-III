#ifndef SIMULATION_SYSTEM_H
#define SIMULATION_SYSTEM_H

#include "Box2D/Dynamics/b2World.h"
#include "entityx/System.h"

namespace triangulum {
namespace system {

class SimulationSystem : public entityx::System<SimulationSystem>
{
public:
  SimulationSystem(b2World& world);

  void update(entityx::EntityManager& entities, entityx::EventManager& events,
              entityx::TimeDelta dt);

private:
  b2World& m_world;

  int32 m_velocityIterations;

  int32 m_positionIterations;
};

}  // namespace system
}  // namespace triangulum

#endif
