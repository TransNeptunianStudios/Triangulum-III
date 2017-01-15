#ifndef _CONNECTION_SYSTEM_H
#define _CONNECTION_SYSTEM_H

#include "entityx/System.h"
#include "triangulum/network/Server.h"

namespace triangulum {

namespace network {
class IConnection;
}

namespace system {

class ConnectionSystem : public entityx::System<ConnectionSystem>
{
public:
   ConnectionSystem();

   void update(entityx::EntityManager &entities,
               entityx::EventManager &events,
               entityx::TimeDelta dt);

private:
   bool does_name_exist(entityx::EntityManager& entities,
                        const std::string& name);

   void send_poistive_reply(network::IConnection* connection, uint64_t id);

   void send_negative_reply(network::IConnection* connection);

   network::Server m_server;
};

} // namespace system
} // namespace triangulum

#endif
