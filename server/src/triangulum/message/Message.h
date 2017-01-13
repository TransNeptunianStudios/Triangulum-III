#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "mongoose.h"
#include "nlohmann/json.hpp"

namespace triangulum {
namespace message {

using BasicJson = nlohmann::basic_json<std::map,
                                       std::vector,
                                       std::string,
                                       bool,
                                       std::int64_t,
                                       std::uint64_t,
                                       double,
                                       std::allocator>;

using Message = std::pair<mg_connection*, BasicJson>;

} // namespace message
} // namespace triangulum

#endif
