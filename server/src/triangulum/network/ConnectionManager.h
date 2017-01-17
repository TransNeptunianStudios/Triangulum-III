#ifndef _CONNECTION_MANAGER_H
#define _CONNECTION_MANAGER_H

#include <functional>
#include <map>

#include "mongoose.h"

#include "triangulum/network/Connection.h"
#include "triangulum/network/IConnectionManager.h"

namespace triangulum {
namespace network {

class ConnectionManager : public IConnectionManager
{
public:
   ConnectionManager();

   ~ConnectionManager();

   void set_incoming_msg(mg_connection* nc, const std::string& msg_type, const Json& msg);

   void remove_connection(mg_connection* nc);

   void accept_connections(std::function<bool(std::shared_ptr<IConnection>)> accept_function);

private:
   using ConnectionMap = std::map<mg_connection*, std::shared_ptr<Connection>>;

   ConnectionMap m_connections;
};

} // namespace network
} // namespace triangulum

#endif
