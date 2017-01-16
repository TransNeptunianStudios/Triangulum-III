#include "triangulum/EntityFactory.h"
#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/Posture.h"
#include "triangulum/component/Velocity.h"

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

   float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/200));
   float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/200));
   entity.assign<Posture>(x, y, 0);

   entity.assign<Velocity>(0, 0, 0);
}

} // namespace triangulum
