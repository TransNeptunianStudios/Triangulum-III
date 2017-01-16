#include "triangulum/component/ClientInfo.h"

namespace triangulum {
namespace component {

using namespace network;

ClientInfo::ClientInfo(std::weak_ptr<network::IConnection> connection_, const std::string& name_)
: connection(connection_)
, name(name_)
{
}

} // namespace component
} // namespace triangulum
