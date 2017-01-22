#include "triangulum/system/OutputSystem.h"

#include "triangulum/component/ClientInfo.h"
#include "triangulum/component/DynamicBody.h"
#include "triangulum/component/Visible.h"
#include "triangulum/network/ConnectionManager.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace component;
using namespace network;

OutputSystem::OutputSystem()
{
}

void OutputSystem::update(EntityManager& entities, EventManager& events,
                          TimeDelta dt)
{
  auto object_list = nlohmann::json::array();

  entities.each<Visible, DynamicBody>(
  [&object_list](Entity entity, Visible& visible, DynamicBody& body) {

    nlohmann::json object;

    object["id"] = entity.id().id();

    object["color"] = visible.color;

    object["sprite"] = visible.sprite;

    object["x"] = body.get_position().x;

    object["y"] = body.get_position().y;

    object["vx"] = 0;

    object["vy"] = 0;

    object_list.push_back(object);

  });

  nlohmann::json resp_msg;

  resp_msg["type"] = "update";

  resp_msg["objects"] = object_list;

  entities.each<ClientInfo>([](Entity entity, ClientInfo& clientinfo) {
    // send to all clients
    if (auto connection = clientinfo.connection.lock())
    {
      //connection->send_msg(resp_msg); // Cannot send this often
    }
  });
}
}  // namespace system
}  // namespace triangulum
