#ifndef _GAME_H
#define _GAME_H

#include "Box2D/Dynamics/b2World.h"
#include "entityx/Event.h"
#include "entityx/Entity.h"
#include "entityx/System.h"

namespace triangulum {

class Game
{
public:
   Game();

   ~Game();

   void init();

   void run();

private:
   void createSystems();

   entityx::EventManager m_event_manager;

   entityx::EntityManager m_entity_manager;

   entityx::SystemManager m_system_manager;

   b2World m_world;
};

} // namespace triangulum

#endif
