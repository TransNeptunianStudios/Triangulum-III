#include "triangulum/component/ClientInfo.h"

namespace triangulum {
namespace component {

ClientInfo::ClientInfo(const std::string& name_,
                       const std::weak_ptr<network::IConnection>& connection_)
: name(name_)
, connection(connection_)
{
}

}  // namespace component
}  // namespace triangulum
