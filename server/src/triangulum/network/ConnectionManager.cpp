#include "triangulum/network/ConnectionManager.h"

namespace triangulum {
namespace network {

ConnectionManager::ConnectionManager()
: m_connections()
{
}

ConnectionManager::~ConnectionManager()
{
}

void ConnectionManager::set_incoming_msg(mg_connection* nc, const std::string& msg_type, const Json& msg)
{
   auto it(m_connections.find(nc));

   if (it != end(m_connections))
   {
      it->second->set_msg(msg_type, msg);
   }
   else
   {
      auto connection(std::make_shared<Connection>(nc));

      connection->set_msg(msg_type, msg);

      m_connections.insert(std::make_pair(nc, connection));
   }
}

void ConnectionManager::remove_connection(mg_connection* nc)
{
   auto it(m_connections.find(nc));

   if (it != end(m_connections))
   {
      m_connections.erase(it);
   }
}

void ConnectionManager::accept_connections(std::function<bool(std::shared_ptr<IConnection>)> accept_function)
{
   for (auto& p : m_connections)
   {
      auto& connection = p.second;

      nlohmann::json dummy_msg;

      if (!connection->is_accepted() && connection->peek_msg("login", dummy_msg))
      {
         if (accept_function(connection))
         {
            connection->set_accepted(true);
         }
      }
   }
}

} // namespace network
} // namespace triangulum
