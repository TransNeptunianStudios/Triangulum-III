#ifndef _GAME_H
#define _GAME_H

#include "entityx/Event.h"
#include "entityx/Entity.h"
#include "entityx/System.h"
#include "triangulum/message/MessageManager.h"

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

   message::MessageManager m_msg_manager;
};

} // namespace triangulum

#endif
