#ifndef _CONNECTION_H
#define _CONNECTION_H

#include "mongoose.h"
#include "nlohmann/json.hpp"
#include "triangulum/network/IConnection.h"

namespace triangulum {
namespace network {

class Connection : public IConnection
{
public:
  Connection(mg_connection* nc);

  ~Connection();

  mg_connection* raw() const;

  void set_msg(const std::string& msg_type, const Json& msg);

  bool get_msg(const std::string& msg_type, Json& msg);

  bool peek_msg(const std::string& msg_type, Json& msg);

  void send_msg(const Json& json);

  void set_accepted(bool is_accepted);

  bool is_accepted() const;

private:
  mg_connection* m_connection;

  bool m_is_accepted;

  // Map message type (string) to json
  using MessageMap = std::map<std::string, Json>;

  MessageMap m_msg_map;
};

}  // namespace system
}  // namespace triangulum

#endif
