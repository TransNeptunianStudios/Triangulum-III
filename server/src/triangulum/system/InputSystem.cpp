#include "triangulum/system/InputSystem.h"
#include "triangulum/component/ClientInfo.h"
#include "triangulum/network/ConnectionManager.h"

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
   entities.each<ClientInfo>([this](Entity entity, ClientInfo& client_info) {
      if (auto connection = client_info.connection.lock())
      {
         Json msg;

         if (connection->get_msg("control", msg))
         {
            std::cout << "Got msg!\n";
         }
      }
   });
}

} // namespace system
} // namespace triangulum
