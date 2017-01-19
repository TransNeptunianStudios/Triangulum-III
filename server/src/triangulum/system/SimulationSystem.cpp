#include "triangulum/system/SimulationSystem.h"

using namespace entityx;

namespace triangulum {
namespace system {

SimulationSystem::SimulationSystem(b2World& world)
: m_world(world)
, m_velocityIterations(8)  // how strongly to correct velocity
, m_positionIterations(3)  // how strongly to correct position
{
}

void SimulationSystem::update(EntityManager& entities, EventManager& events,
                              TimeDelta dt)
{
  m_world.Step(dt, m_velocityIterations, m_positionIterations);
}

}  // namespace system
}  // namespace triangulum
