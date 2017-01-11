#ifndef _GAME_H
#define _GAME_H

#include "entityx/Event.h"
#include "entityx/Entity.h"
#include "entityx/System.h"

#include "moodycamel/readerwriterqueue.h"

#include "triangulum/component/PlayerInfo.h"

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

   moodycamel::ReaderWriterQueue<component::PlayerInfo> m_player_info_queue;

   moodycamel::ReaderWriterQueue<int> m_input_queue;

   moodycamel::ReaderWriterQueue<int> m_output_queue;
};

} // namespace triangulum

#endif
