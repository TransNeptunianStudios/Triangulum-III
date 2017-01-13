#ifndef _MESSAGE_MAP_H
#define _MESSAGE_MAP_H

#include <functional>
#include <map>
#include <queue>
#include "triangulum/message/Message.h"

namespace triangulum {
namespace message {

using MessageQueue = std::queue<Message>;

using MessageMap = std::map<std::string, MessageQueue>;

void for_each_msg(MessageMap& msg_map,
                  std::string type,
                  std::function<void(const Message&)> f);

void for_each_json(MessageMap& msg_map,
                   std::string type,
                   std::function<void(const BasicJson&)> f);

void for_all_msg(MessageMap& msg_map,
                 std::function<void(const Message&)> f);

} // namespace message
} // namespace triangulum

#endif
