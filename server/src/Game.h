#ifndef _GAME_H
#define _GAME_H

#include "entityx/Event.h"
#include "entityx/Entity.h"
#include "entityx/System.h"

class Game
{
public:
   Game();
   ~Game();
private:
   entityx::EventManager m_eventManager;
   entityx::EntityManager m_entityManager;
   entityx::SystemManager m_systemManager;
};

#endif
