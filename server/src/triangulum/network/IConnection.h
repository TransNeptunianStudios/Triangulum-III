#ifndef _I_CONNECTION_H
#define _I_CONNECTION_H

#include "mongoose.h"
#include "nlohmann/json.hpp"

namespace triangulum {
namespace network {

using Json =
nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t,
                     std::uint64_t, double, std::allocator>;

class IConnection
{
public:
  virtual ~IConnection() {}

  virtual bool get_msg(const std::string& msg_type, Json& msg) = 0;

  virtual bool peek_msg(const std::string& msg_type, Json& msg) = 0;

  virtual void send_msg(const Json& json) = 0;
};

}  // namespace system
}  // namespace triangulum

#endif
