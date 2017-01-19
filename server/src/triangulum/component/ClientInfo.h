#ifndef _CLIENT_INFO_H
#define _CLIENT_INFO_H

#include "entityx/Entity.h"

namespace triangulum {

namespace network {
class IConnection;
}

namespace component {

struct ClientInfo : public entityx::Component<ClientInfo>
{
  ClientInfo(const std::string& name_,
             const std::weak_ptr<network::IConnection>& connection_);

  std::string name;

  std::weak_ptr<network::IConnection> connection;
};

}  // namespace component
}  // namespace triangulum

#endif
