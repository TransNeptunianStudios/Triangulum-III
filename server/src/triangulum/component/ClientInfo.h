#ifndef _CLIENT_INFO_H
#define _CLIENT_INFO_H

#include "entityx/Entity.h"
#include "triangulum/network/Connection.h"

namespace triangulum {
namespace component {

struct ClientInfo : public entityx::Component<ClientInfo>
{
   ClientInfo(network::IConnection* connection_,
              const std::string& name_);

   network::IConnection* connection;

   std::string name;
};

} // namespace component
} // namespace triangulum

#endif
