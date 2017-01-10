#ifndef _GAME_H
#define _GAME_H

#include "entityx/Event.h"
#include "entityx/Entity.h"
#include "entityx/System.h"

#include "triangulum/web/WebServer.h"

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

   entityx::EventManager m_eventManager;

   entityx::EntityManager m_entityManager;

   entityx::SystemManager m_systemManager;

   web::WebServer m_webServer;
};

} // namespace triangulum

#endif
