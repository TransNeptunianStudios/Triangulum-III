#include "triangulum/message/MessageManager.h"
#include "nlohmann/json.hpp"

namespace triangulum {
namespace message {

MessageManager::MessageManager()
: m_msg_input()
, m_msg_output()
{
   reg_input_msg("login");

   reg_output_msg("login_resp");
}

void MessageManager::parse_buffer(mg_connection* nc, const char* buffer)
{
   // TODO: Try-catch?
   auto msg = nlohmann::json::parse(buffer);

   auto msg_type = msg["type"];

   if (!msg_type.is_string())
   {
      return;
   }

   // TODO: Add some kind of validator for each message
   MessageMap::iterator it(m_msg_input.find(msg_type));

   if (it != end(m_msg_input))
   {
      it->second.push(std::make_pair(nc, msg));
   }
}

void MessageManager::add_output(std::string msg_type, const Message& msg)
{
   MessageMap::iterator it(m_msg_output.find(msg_type));

   if (it != end(m_msg_output))
   {
      it->second.push(msg);
   }
}

MessageMap& MessageManager::input_map()
{
   return m_msg_input;
}

MessageMap& MessageManager::output_map()
{
   return m_msg_output;
}

void MessageManager::reg_input_msg(std::string msg_type)
{
   m_msg_input.insert(std::make_pair(msg_type, MessageQueue()));
}

void MessageManager::reg_output_msg(std::string msg_type)
{
  m_msg_output.insert(std::make_pair(msg_type, MessageQueue()));
}

} // namespace message
} // namespace triangulum
