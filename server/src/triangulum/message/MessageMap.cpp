#include "triangulum/message/MessageMap.h"

namespace triangulum {
namespace message {

void for_each_msg(MessageMap& msg_map,
                  std::string type,
                  std::function<void(const Message&)> f)
{
   MessageMap::iterator it(msg_map.find(type));

   if (it == end(msg_map))
   {
      return;
   }

   auto& msg_queue(it->second);

   while (!msg_queue.empty())
   {
      auto& msg(msg_queue.front());

      f(msg);

      msg_queue.pop();
   }
}

void for_each_json(MessageMap& msg_map,
                   std::string type,
                   std::function<void (const BasicJson &)> f)
{
   MessageMap::iterator it(msg_map.find(type));

   if (it == end(msg_map))
   {
      return;
   }

   auto& msg_queue(it->second);

   while (!msg_queue.empty())
   {
      auto& msg(msg_queue.front());

      f(msg.second);

      msg_queue.pop();
   }
}

void for_all_msg(MessageMap& msg_map, std::function<void (const Message &)> f)
{
   for (auto& p : msg_map)
   {
      auto& msg_queue = p.second;

      while (!msg_queue.empty())
      {
         auto& msg(msg_queue.front());

         f(msg);

         msg_queue.pop();
      }
   }
}

} // namespace message
} // namespace triangulum
