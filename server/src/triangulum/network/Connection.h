#ifndef _CONNECTION_H
#define _CONNECTION_H

#include "mongoose.h"
#include "nlohmann/json.hpp"

namespace triangulum {
namespace network {

using Json = nlohmann::basic_json<std::map,
                                       std::vector,
                                       std::string,
                                       bool,
                                       std::int64_t,
                                       std::uint64_t,
                                       double,
                                       std::allocator>;

// Map message type (string) to json
using MessageMap = std::map<std::string, Json>;

class IConnection
{
public:
   virtual ~IConnection() {}

   virtual bool get_msg(const std::string& msg_type, Json& msg) = 0;

   virtual bool peek_msg(const std::string& msg_type, Json& msg) = 0;

   virtual void send_msg(const Json& json) = 0;
};

class Connection : public IConnection
{
public:
   Connection(mg_connection* nc);

   ~Connection();

   mg_connection* raw() const;

   void set_accepted(bool is_accepted);

   bool is_accepted() const;

   void set_msg(const std::string& msg_type, const Json& msg);

   bool get_msg(const std::string& msg_type, Json& msg);

   bool peek_msg(const std::string& msg_type, Json& msg);

   void send_msg(const Json& json);

private:
   mg_connection* m_connection;

   MessageMap m_msg_map;

   bool m_is_accepted;
};

} // namespace system
} // namespace triangulum

#endif
