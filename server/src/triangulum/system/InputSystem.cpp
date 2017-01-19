#include "triangulum/system/InputSystem.h"
#include "Box2D/Dynamics/b2Body.h"

#include <bitset>

#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/network/ConnectionManager.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;
using namespace network;

InputSystem::InputSystem() {}

void InputSystem::update(EntityManager& entities, EventManager& events,
                         TimeDelta dt)
{
  entities.each<ClientInfo, DynamicBody>(
  [](Entity entity, ClientInfo& client_info, DynamicBody& body) {
    if (auto connection = client_info.connection.lock())
    {
      Json msg;

      if (connection->get_msg("control",
                              msg))  //&& msg["input_mask"].is_integer())
      {
        // thurst, reverse, strafe Left, strafe right, turn left, turn
        // right, fire weapon, not used
        int inputMask = msg["input_mask"];
        std::string inputBits = std::bitset<8>(inputMask).to_string();

        // Move around regardless of orientation, wrong, but will suffice
        // for now.
        float speed = 1;
        int xDir = int(inputBits[3] - '0') - int(inputBits[2] - '0');
        int yDir = int(inputBits[0] - '0') - int(inputBits[1] - '0');
        body.apply_force(b2Vec2((float)xDir * speed, (float)yDir * speed));

        // Rotate
        float rotSpeed = 1;
        int rotDir = int(inputBits[5] - '0') - int(inputBits[4] - '0');
        body.apply_torque(rotDir * rotSpeed);

        // Shoot
        if (int(inputBits[6] - '0') != 0)
        {
          std::cout << "Pew pew\n";
        }

        b2Vec2 pos = body.body->GetPosition();
        std::cout << "Position: (" << pos.x << ", " << pos.y << ")\n";
      }
    }
  });
}

}  // namespace system
}  // namespace triangulum
