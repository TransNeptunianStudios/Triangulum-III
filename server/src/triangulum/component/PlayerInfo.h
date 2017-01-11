#ifndef _PLAYER_INFO_H
#define _PLAYER_INFO_H

#include "mongoose.h"
#include "entityx/Entity.h"

namespace triangulum {
namespace component {

struct PlayerInfo : public entityx::Component<PlayerInfo>
{
   PlayerInfo();

   mg_connection* connection;

   std::string name;
};

} // namespace component
} // namespace triangulum

#endif
