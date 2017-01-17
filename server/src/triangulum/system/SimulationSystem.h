#ifndef SIMULATION_SYSTEM_H
#define SIMULATION_SYSTEM_H

#include "entityx/System.h"
#include "Box2D/Dynamics/b2World.h"

namespace triangulum {
namespace system {

class SimulationSystem : public entityx::System<SimulationSystem>
{
public:
   SimulationSystem(b2World& world);

   void update(entityx::EntityManager &entities,
               entityx::EventManager &events,
               entityx::TimeDelta dt);

   b2World& m_world;
};

} // namespace system
} // namespace triangulum

#endif
