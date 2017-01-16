#include "triangulum/system/InputSystem.h"
#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/Posture.h"
#include "triangulum/component/Velocity.h"

#include <bitset>

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
   entities.each<ClientInfo, Velocity>([](
     Entity entity,
     ClientInfo& client_info,
     Velocity& vel) {
      if (auto connection = client_info.connection.lock())
      {
         Json msg;

         if (connection->get_msg("control", msg) ) //&& msg["input_mask"].is_integer())
         {
             // thurst, reverse, strafe Left, strafe right, turn left, turn right, fire weapon, not used
             int inputMask = msg["input_mask"];
             std::string inputBits = std::bitset< 8 >( inputMask ).to_string(); // string conversion
             std::cout << "Got Input " << inputBits << " from " << client_info.name << std::endl;

             float speed = 1;
             vel.vx = (int(inputBits[3]- '0') * speed) - (int(inputBits[2]- '0') * speed);
             vel.vy = (int(inputBits[0]- '0') * speed) - (int(inputBits[1]- '0') * speed);

             float rotSpeed = 1;
             vel.vr = (int(inputBits[5]- '0') * rotSpeed) - (int(inputBits[4]- '0') * rotSpeed);

             if(int(inputBits[6]- '0') != 0)
                std::cout << "Pew pew" << std::endl;
         }
      }
   });
}

} // namespace system
} // namespace triangulum
