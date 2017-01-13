#ifndef _CONNECTION_SYSTEM_H
#define _CONNECTION_SYSTEM_H

#include "entityx/System.h"
#include "triangulum/message/MessageManager.h"

namespace triangulum {
namespace system {

class ConnectionSystem : public entityx::System<ConnectionSystem>
{
public:
   ConnectionSystem(message::MessageManager& m_msg_manager);

   void update(entityx::EntityManager &entities,
               entityx::EventManager &events,
               entityx::TimeDelta dt);

private:
   message::MessageManager& m_msg_manager;
};

} // namespace system
} // namespace triangulum

#endif
