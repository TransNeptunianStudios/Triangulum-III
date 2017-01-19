#ifndef _CONNECTION_SYSTEM_H
#define _CONNECTION_SYSTEM_H

#include "entityx/System.h"
#include "triangulum/EntityFactory.h"

namespace triangulum {

namespace network {
class IConnection;
class IConnectionManager;
}

namespace system {

class ConnectionSystem : public entityx::System<ConnectionSystem>
{
public:
  ConnectionSystem(network::IConnectionManager &connection_mgr,
                   EntityFactory &entity_factory);

  void update(entityx::EntityManager &entities, entityx::EventManager &events,
              entityx::TimeDelta dt);

private:
  bool does_name_exist(entityx::EntityManager &entities,
                       const std::string &name);

  void send_poistive_reply(std::shared_ptr<network::IConnection> connection,
                           uint64_t id);

  void send_negative_reply(std::shared_ptr<network::IConnection> connection);

  network::IConnectionManager &m_connection_mgr;

  EntityFactory m_entity_factory;
};

}  // namespace system
}  // namespace triangulum

#endif
