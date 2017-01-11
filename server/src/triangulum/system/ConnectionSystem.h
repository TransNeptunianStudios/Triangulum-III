#ifndef _CONNECTION_SYSTEM_H
#define _CONNECTION_SYSTEM_H

#include "entityx/System.h"

#include "moodycamel/readerwriterqueue.h"

#include "triangulum/component/PlayerInfo.h"

namespace triangulum {
namespace system {

class ConnectionSystem : public entityx::System<ConnectionSystem>
{
public:
   ConnectionSystem(moodycamel::ReaderWriterQueue<component::PlayerInfo>& player_info_queue);

   void update(entityx::EntityManager &entities,
               entityx::EventManager &events,
               entityx::TimeDelta dt);
private:
   moodycamel::ReaderWriterQueue<component::PlayerInfo>& m_player_info_queue;
};

} // namespace system
} // namespace triangulum

#endif
