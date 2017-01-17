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
                                  const std::string& name,
                                  const std::weak_ptr<IConnection>& connection)
{
   entity.assign<ClientInfo>(name, connection);
}

} // namespace triangulum
