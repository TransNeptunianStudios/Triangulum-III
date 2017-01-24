#include "triangulum/system/ControlSystem.h"
#include "Box2D/Dynamics/b2Body.h"

#include <bitset>

#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/Input.h"
#include "triangulum/network/ConnectionManager.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;
using namespace network;

ControlSystem::ControlSystem()
{
}

void ControlSystem::update(EntityManager& entities,
                           EventManager& events,
                           TimeDelta dt)
{
  entities.each<ClientInfo, Input>(
  [](Entity entity, ClientInfo& client_info, Input& input) {
    if (auto connection = client_info.connection.lock())
    {
      Json msg;

      if (connection->get_msg("control", msg))
      {
        if (msg["input_mask"].is_number_integer())
        {
          // thurst, reverse, strafe Left, strafe right, turn left, turn
          // right, fire weapon, not used
          int inputMask = msg["input_mask"];
          std::string inputBits = std::bitset<8>(inputMask).to_string();

          input.thrust = inputBits[0] != '0';
          input.reverse = inputBits[1] != '0';
          input.strafe_left = inputBits[2] != '0';
          input.strafe_right = inputBits[3] != '0';
          input.turn_left = inputBits[4] != '0';
          input.turn_right = inputBits[5] != '0';
          input.fire = inputBits[6] != '0';
          input.spare = inputBits[7] != '0';
        }
      }
    }
  });
}

}  // namespace system
}  // namespace triangulum
