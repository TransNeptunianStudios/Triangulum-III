#include "triangulum/network/Connection.h"

namespace triangulum {
namespace network {

Connection::Connection(mg_connection *nc)
: m_connection(nc)
, m_msg_map()
, m_is_accepted(false)
{
   // Incoming messages
   m_msg_map.insert(std::make_pair("login", Json()));
   m_msg_map.insert(std::make_pair("control", Json()));

   // Outgoing messages
   m_msg_map.insert(std::make_pair("login_resp", Json()));
}

Connection::~Connection()
{
}

mg_connection* Connection::raw() const
{
   return m_connection;
}

void Connection::set_accepted(bool is_accepted)
{
   m_is_accepted = is_accepted;
}

bool Connection::is_accepted() const
{
   return m_is_accepted;
}

void Connection::set_msg(const std::string& msg_type, const Json& msg)
{
   MessageMap::iterator it(m_msg_map.find(msg_type));

   if (it != end(m_msg_map))
   {
      it->second = msg;
   }
}

bool Connection::get_msg(const std::string& msg_type, Json& msg)
{
   MessageMap::iterator it(m_msg_map.find(msg_type));

   if (it != end(m_msg_map))
   {
      if (it->second.empty())
      {
         return false;
      }
      else
      {
         msg = it->second;

         it->second = nlohmann::json::object();

         return true;
      }
   }

   return false;
}

bool Connection::peek_msg(const std::string& msg_type, Json& msg)
{
   MessageMap::iterator it(m_msg_map.find(msg_type));

   if (it != end(m_msg_map))
   {
      if (it->second.empty())
      {
         return false;
      }
      else
      {
         msg = it->second;

         return true;
      }
   }

   return false;
}

void Connection::send_msg(const Json& json)
{
   std::string json_msg = json.dump(0);

   mg_send_websocket_frame(m_connection,
                           WEBSOCKET_OP_TEXT,
                           json_msg.c_str(),
                           json_msg.size());
}

} // namespace system
} // namespace triangulum
