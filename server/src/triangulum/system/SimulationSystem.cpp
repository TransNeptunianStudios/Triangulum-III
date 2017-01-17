#include "triangulum/system/SimulationSystem.h"

using namespace entityx;

namespace triangulum {
namespace system {

SimulationSystem::SimulationSystem(b2World& world)
: m_world(world)
{
}

void SimulationSystem::update(EntityManager& entities,
                              EventManager& events,
                              TimeDelta dt)
{
  int32 velocityIterations = 8;   //how strongly to correct velocity
  int32 positionIterations = 3;   //how strongly to correct position

  m_world.Step( dt, velocityIterations, positionIterations);
}

} // namespace system
} // namespace triangulum
