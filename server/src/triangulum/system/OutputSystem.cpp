#include "triangulum/system/OutputSystem.h"

#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Graphics.h"
#include "triangulum/component/Score.h"
#include "triangulum/component/Health.h"
#include "triangulum/network/ConnectionManager.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;
using namespace network;

OutputSystem::OutputSystem()
{
}

void OutputSystem::update(EntityManager& entities,
                          EventManager& events,
                          TimeDelta dt)
{
  auto object_list = nlohmann::json::array();

  entities.each<Graphics, DynamicBody>(
				       [&object_list](Entity entity, Graphics& graphics, DynamicBody& body) {

    nlohmann::json object;

    object["id"] = entity.id().id();

    object["color"] = graphics.color;

    object["sprite"] = graphics.sprite;

    object["width"] = graphics.width;

    object["height"] = graphics.height;

    object["x"] = body.get_position().x;

    object["y"] = body.get_position().y;

    object["vx"] = 0;

    object["vy"] = 0;

    object["r"] = body.get_rotation();

    object["vr"] = 0;
    
    ComponentHandle<Score> score = entity.component<Score>();
    if (score) {
      object["score"] = (int)score->score;
    }

    ComponentHandle<Health> health = entity.component<Health>();
    if (health) {
      object["health"] = (int)health->health;
    }
    
    object_list.push_back(object);

  });

  nlohmann::json resp_msg;

  resp_msg["type"] = "update";

  resp_msg["objects"] = object_list;

  //std::cout << resp_msg.dump(2);

  entities.each<ClientInfo>([&resp_msg](Entity entity, ClientInfo& clientinfo) {
    // send to all clients
    if (auto connection = clientinfo.connection.lock())
    {
      connection->send_msg(resp_msg);  // Cannot send this often
    }
  });
}
}  // namespace system
}  // namespace triangulum
