#include "triangulum/system/InputSystem.h"
#include "triangulum/component/ClientInfo.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;
using namespace network;

InputSystem::InputSystem()
{
}

void InputSystem::update(EntityManager& entities,
                         EventManager& events,
                         TimeDelta dt)
{
   entities.each<ClientInfo>([](Entity entity, ClientInfo& client_info) {
      Json msg;

      if (client_info.connection->get_msg("control", msg))
      {
         // TODO: Update input
      }
   });
}

} // namespace system
} // namespace triangulum
