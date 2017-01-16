#include "triangulum/EntityFactory.h"
#include "triangulum/component/ClientInfo.h"

using namespace entityx;

namespace triangulum {

using namespace component;
using namespace network;

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

void EntityFactory::create_player(Entity entity,
                                  std::weak_ptr<network::IConnection> connection,
                                  const std::string& name)
{
   entity.assign<ClientInfo>(connection, name);
}

} // namespace triangulum
