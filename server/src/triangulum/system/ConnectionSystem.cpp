#include "triangulum/system/ConnectionSystem.h"

using namespace entityx;

namespace triangulum {
namespace system {

using namespace message;

ConnectionSystem::ConnectionSystem(MessageManager& msg_manager)
: m_msg_manager(msg_manager)
{
}

void ConnectionSystem::update(EntityManager& entities,
                              EventManager& events,
                              TimeDelta dt)
{
   for_each_msg(m_msg_manager.input_map(), "login", [this](const Message& in_msg){
      // TODO: Check if username is not used.
      nlohmann::json msg;
      msg["type"] = "login_resp";
      msg["status"] = "success";
      msg["id"] = 123;

      auto out_msg(std::make_pair(in_msg.first, msg));

      m_msg_manager.add_output("login_resp", out_msg);
   });
}

} // namespace system
} // namespace triangulum
