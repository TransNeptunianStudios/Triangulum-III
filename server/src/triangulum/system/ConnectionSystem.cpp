
#include "triangulum/system/ConnectionSystem.h"

using namespace entityx;
using namespace moodycamel;

namespace triangulum {
namespace system {

using namespace component;

ConnectionSystem::ConnectionSystem(ReaderWriterQueue<PlayerInfo>& player_info_queue)
: m_player_info_queue(player_info_queue)
{
}

void ConnectionSystem::update(EntityManager& entities,
                              EventManager& events,
                              TimeDelta dt)
{
   PlayerInfo player_info;

   while (m_player_info_queue.try_dequeue(player_info))
   {
      std::cout << "Creating new player: " << player_info.name << "\n";
   }
}

} // namespace system
} // namespace triangulum
